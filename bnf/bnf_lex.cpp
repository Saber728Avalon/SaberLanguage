#include "bnf_lex.h"
#include "bnf_lex_header.h"


inline void PushList(std::vector<BNFLexItem> &list, MainBNFLexType mainType, int subType, const char *pszChar, int nLen)
{
	BNFLexItem item;
	item.mainType = mainType;
	item.subType = subType;
	//��������
	try {
		item.strInfo.resize(nLen + 1);
		//����\0
		item.strInfo[nLen] = '\0';
		item.strInfo.resize(nLen);
	} catch(...) {
	}
	memcpy((void *)item.strInfo.c_str(), pszChar, nLen);
	//����
	list.emplace_back(item);
}

int TogetherStr(const char *pszStart, int nLen, std::vector<BNFLexItem> &list )
{
	bool bIsStr = false;
	int i = 0;
	while ('_' == pszStart[i]
	|| (pszStart[i] <= 'Z' && pszStart[i] >= 'A')
		|| (pszStart[i] <= 'z' && pszStart[i] >= 'a')
		|| (pszStart[i] <= '9' && pszStart[i] >= '0')) {	
			i++;
	}
	if (i > 0) { //��ʼ������������
		bool bIsInnerKeyWork = false;
		for (int j = 0; j < sizeof(SubBNFKeyWordStr) / sizeof(char *); j++) {
			if ( 0 == strncmp(SubBNFKeyWordStr[j], pszStart, i)) {
				bIsInnerKeyWork = true;
				PushList(list, MainBNFLexType::MainBNFKeyWord, int(SubBNFKeyWord::SubBNFKEYDoubleQuote) + j, pszStart,  i);
				break;
			}
		}
		if (!bIsInnerKeyWork) {
			PushList(list, MainBNFLexType::MainBNFCoustom, 0, pszStart, i);
		}
	}
	return i;
}

int bnf_lex(const char *pszSrc, int nLen, std::vector<BNFLexItem> &list)
{
	//��¼����״̬����Ҫ�����ע�����ַ���
	AnalyzeState analyzeState = AnalyzeState::AnalyzeUnknown;

	for (int i = 0; i < nLen; ) {
		//��ǰ״̬��˫б�ܵ�ע��
		if (AnalyzeState::AnalyzeCommentForwardSlash == analyzeState) {
			while(i < nLen && '\n' != pszSrc[i]) {//����ע��,ע�ͽ�β�ǻ���
				i++;
			}
			i++;//���� \n ע�ͽ�������
			analyzeState = AnalyzeState::AnalyzeUnknown;//��������״̬
			continue;
		} else if (AnalyzeState::AnalyzeCommentSlashStar == analyzeState) {//��ǰ״̬��/*ע��
			while ((i + 1 < nLen) && ('*' != pszSrc[i]) && ('/' != pszSrc[i + 1])) {//����ע�ͣ�ע�ͽ�β�� */
				i++;
			}
			i += 2;//���� */ ע�ͽ�������
			analyzeState = AnalyzeState::AnalyzeUnknown;//��������״̬
			continue;
		} else if (AnalyzeState::AnalyzeStringStart == analyzeState) {//��ǰ״̬���ַ���
			int nStart = i;
			while (i + 1 < nLen) {//�����ַ�����ֱ���ַ�������
				if ('\"' != pszSrc[i]) {
					i++;
					continue;
				}
				if ('\\' == pszSrc[i - 1]) {
					i++;
					continue;
				}
				break;
			}
			PushList(list, MainBNFLexType::MainBNFStr, 0, pszSrc + nStart, i - nStart);
			i++;//��������"
			analyzeState = AnalyzeState::AnalyzeUnknown;//��������״̬
			continue;
		}
		//���˵����еȷ���
		if (' ' == pszSrc[i]
		|| '\r' == pszSrc[i]
		|| '\t' == pszSrc[i]) {
			i++;
			continue;
		}

		//�ۺ��ַ���,��������ʼ���ַ����ۺϵ�һ��
		int nTogetherLen = TogetherStr(pszSrc + i, nLen - i, list);
		if (nTogetherLen > 0) {
			i += nTogetherLen;
			continue;
		}


		switch(pszSrc[i])
		{
		case '/':{
			if (i + 1 >= nLen){//�����쳣���
				return 0;
			}
			if ('/'== pszSrc[i + 1]) { //˫б��ע�Ϳ�ʼ
				analyzeState = AnalyzeState::AnalyzeCommentForwardSlash;
				i++;
			} else if ('*'== pszSrc[i + 1]) {//   /*ע�Ϳ�ʼ
				analyzeState = AnalyzeState::AnalyzeCommentSlashStar;
				i++;
			} 
				 }
				 break;
		case '{': {
			PushList(list, MainBNFLexType::MainBNFSymbol, int(SubBNFSymbol::SubBNFSymbolBraceLeft), "{", 1);
				  }
				  break;
		case '}': {
			PushList(list, MainBNFLexType::MainBNFSymbol, int(SubBNFSymbol::SubBNFSymbolBraceRight), "}", 1);
				  }
				  break;
		case '[':{
			PushList(list, MainBNFLexType::MainBNFSymbol, int(SubBNFSymbol::SubBNFSymbolBracketsLeft), "[", 1);
				 }
				 break;
		case ']': {
			PushList(list, MainBNFLexType::MainBNFSymbol, int(SubBNFSymbol::SubBNFSymbolBracketsRight), "]", 1);
				  }
				  break;
		case '(':{
			PushList(list, MainBNFLexType::MainBNFSymbol, int(SubBNFSymbol::SubBNFSymbolParenthesisLeft), "(", 1);
				 }
				 break;
		case ')': {
			PushList(list, MainBNFLexType::MainBNFSymbol, int(SubBNFSymbol::SubBNFSymbolParenthesisRight), ")", 1);
				  }
				  break;
		case '|': {
			PushList(list, MainBNFLexType::MainBNFSymbol, int(SubBNFSymbol::SubBNFSymbolOr), "|", 2);
				  }
				  break;
				  //case '>': {//����ʵ����û���ã�����������ʱ��
				  //	PushList(list, MainBNFLexType::MainBNFSymbol, int(SubBNFSymbol::SubBNFSymbolLarge), ">", 1);
				  //		  }
				  //		  break;
				  //case '<': {
				  //	PushList(list, MainBNFLexType::MainBNFSymbol, int(SubBNFSymbol::SubBNFSymbolLess), "<", 1);
				  //		  }
				  //		  break;
		case ':': {
			if (i + 2 >= nLen){//�����쳣���
				return 0;
			}
			if (':' == pszSrc[i + 1] && '=' ==  pszSrc[i + 2]) {
				PushList(list, MainBNFLexType::MainBNFSymbol, int(SubBNFSymbol::SubBNFSymbolDefinit), "::=", 3);
				i += 2;
			}
				  }
				  break;
		case '\n': {
			PushList(list, MainBNFLexType::MainBNFLineEnd, 0, "\\n", 2);
			while (i + 1 < nLen){//�����쳣���
				if ('\r' == pszSrc[i + 1] || '\n' ==  pszSrc[i + 1]) {//���л���ʱ��û��Ҫ������ô�������
					i++;
				} else {
					break;
				}
			}
				   }
				   break;
		case '\'': {
			if (i + 2 >= nLen){//�����쳣���
				return 0;
			}
			if ('\'' == pszSrc[i + 2]) {
				PushList(list, MainBNFLexType::MainBNFChar, 0, &pszSrc[i + 1], 1);//���һ���ַ�
			}
				   }
				   break;
		case '\"': {//��ӵ����ַ���
			analyzeState = AnalyzeState::AnalyzeStringStart;
				   }
				   break;

		default:
			break;
		}
		i++;
	}
	return 0;
}

int dump_bnf_lex(std::vector<BNFLexItem> &listItem, const char *pszFilePath)
{
	char buf[1024];
	FILE *pFile = fopen(pszFilePath, "wb");
	if (nullptr == pFile) {
		return 0;
	}
	for (auto iter = listItem.begin(); iter != listItem.end(); iter++)
	{
		sprintf(buf, "(%d, 0x%x, %s)\n", iter->mainType, iter->subType, iter->strInfo.c_str());
		fwrite(buf, 1, strlen(buf), pFile);
	}
	fclose(pFile);

	return 0;
}