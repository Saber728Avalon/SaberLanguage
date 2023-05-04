#include "bnf_lex.h"
#include "bnf_lex_header.h"


inline void PushList(std::vector<BNFLexItem> &list, MainBNFLexType mainType, int subType, const char *pszChar, int nLen)
{
	BNFLexItem item;
	item.mainType = mainType;
	item.subType = subType;
	//保存数据
	try {
		item.strInfo.resize(nLen + 1);
		//增加\0
		item.strInfo[nLen] = '\0';
		item.strInfo.resize(nLen);
	} catch(...) {
	}
	memcpy((void *)item.strInfo.c_str(), pszChar, nLen);
	//插入
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
	if (i > 0) { //开始分析所属类型
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
	//记录特殊状态，主要是针对注释与字符串
	AnalyzeState analyzeState = AnalyzeState::AnalyzeUnknown;

	for (int i = 0; i < nLen; ) {
		//当前状态是双斜杠的注释
		if (AnalyzeState::AnalyzeCommentForwardSlash == analyzeState) {
			while(i < nLen && '\n' != pszSrc[i]) {//跳过注释,注释结尾是换行
				i++;
			}
			i++;//跳过 \n 注释结束符号
			analyzeState = AnalyzeState::AnalyzeUnknown;//重置特殊状态
			continue;
		} else if (AnalyzeState::AnalyzeCommentSlashStar == analyzeState) {//当前状态是/*注释
			while ((i + 1 < nLen) && ('*' != pszSrc[i]) && ('/' != pszSrc[i + 1])) {//跳过注释，注释结尾是 */
				i++;
			}
			i += 2;//跳过 */ 注释结束符号
			analyzeState = AnalyzeState::AnalyzeUnknown;//重置特殊状态
			continue;
		} else if (AnalyzeState::AnalyzeStringStart == analyzeState) {//当前状态是字符串
			int nStart = i;
			while (i + 1 < nLen) {//处理字符串，直到字符串结束
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
			i++;//跳过结束"
			analyzeState = AnalyzeState::AnalyzeUnknown;//重置特殊状态
			continue;
		}
		//过滤掉换行等符号
		if (' ' == pszSrc[i]
		|| '\r' == pszSrc[i]
		|| '\t' == pszSrc[i]) {
			i++;
			continue;
		}

		//聚合字符串,将附近开始的字符串聚合到一起。
		int nTogetherLen = TogetherStr(pszSrc + i, nLen - i, list);
		if (nTogetherLen > 0) {
			i += nTogetherLen;
			continue;
		}


		switch(pszSrc[i])
		{
		case '/':{
			if (i + 1 >= nLen){//处理异常情况
				return 0;
			}
			if ('/'== pszSrc[i + 1]) { //双斜杠注释开始
				analyzeState = AnalyzeState::AnalyzeCommentForwardSlash;
				i++;
			} else if ('*'== pszSrc[i + 1]) {//   /*注释开始
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
				  //case '>': {//这俩实在是没有用，还妨碍分析时候
				  //	PushList(list, MainBNFLexType::MainBNFSymbol, int(SubBNFSymbol::SubBNFSymbolLarge), ">", 1);
				  //		  }
				  //		  break;
				  //case '<': {
				  //	PushList(list, MainBNFLexType::MainBNFSymbol, int(SubBNFSymbol::SubBNFSymbolLess), "<", 1);
				  //		  }
				  //		  break;
		case ':': {
			if (i + 2 >= nLen){//处理异常情况
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
			while (i + 1 < nLen){//处理异常情况
				if ('\r' == pszSrc[i + 1] || '\n' ==  pszSrc[i + 1]) {//多行换行时候，没必要保存那么多结束符
					i++;
				} else {
					break;
				}
			}
				   }
				   break;
		case '\'': {
			if (i + 2 >= nLen){//处理异常情况
				return 0;
			}
			if ('\'' == pszSrc[i + 2]) {
				PushList(list, MainBNFLexType::MainBNFChar, 0, &pszSrc[i + 1], 1);//添加一个字符
			}
				   }
				   break;
		case '\"': {//添加的是字符串
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