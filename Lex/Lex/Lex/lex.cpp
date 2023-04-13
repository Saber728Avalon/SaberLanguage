#include "lex.h"
#include "lex_header.h"

inline void PushList(std::vector<LexItem> &list, MainLexType mainType, int subType, const char *pszChar, int nLen)
{
	LexItem item;
	item.mainType = mainType;
	item.subType = subType;
	//保存数据
	try {
		item.strInfo.resize(nLen + 4);
	} catch(...) {
	}
	memcpy((void *)item.strInfo.c_str(), pszChar, nLen);
	//增加\0
	item.strInfo[nLen] = '\0';
	//插入
	list.emplace_back(item);
}

int TogetherStr(const char *pszStart, int nLen, std::vector<LexItem> &list )
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
		for (int j = 0; j < sizeof(SubKeyWordStr) / sizeof(char *); j++) {
			if ( 0 == strncmp(SubKeyWordStr[j], pszStart, i)) {
				bIsInnerKeyWork = true;
				PushList(list, MainLexType::MainKeyWord, int(SubKeyWord::SubI8) + j, pszStart,  i);
				break;
			}
		}
		if (!bIsInnerKeyWork) {
			PushList(list, MainLexType::MainCustom, int(SubCustom::SubParam), pszStart, i);
		}
	}
	return i;
}

int Lex(const char *pszSrc, int nLen, std::vector<LexItem> &list)
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
			PushList(list, MainLexType::MainCustom, int(SubCustom::SubString), pszSrc + nStart, i - nStart);
			i++;//跳过结束"
			analyzeState = AnalyzeState::AnalyzeUnknown;//重置特殊状态
			continue;
		}

		//过滤掉换行等符号
		if (' ' == pszSrc[i]
			|| '\r' == pszSrc[i]
			|| '\n' == pszSrc[i]
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
		case ';': {
			PushList(list, MainLexType::MainSpace, int(SubSpace::SubSemicolon), ";", 1);
				  }
				  break;
		case '+': {
			PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubAdd), "+", 1);
				  }
				break;
		case '-': {
			PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubSub), "-", 1);
				  }
				  break;
		case '*': {
			PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubMul), "*", 1);
				  }
				  break;
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
			} else {//说明是除法
				PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubDiv), "/", 1);
			}
			}
				 break;
		case '{': {
			PushList(list, MainLexType::MainSymbol, int(SubSpace::SubBraceLeft), "{", 1);
				  }
				  break;
		case '}': {
			PushList(list, MainLexType::MainSymbol, int(SubSpace::SubBraceRight), "}", 1);
				  }
				  break;
		case '[':{
			PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubBracketsLeft), "[", 1);
				 }
				 break;
		case ']': {
			PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubBracketsRight), "]", 1);
				  }
				  break;
		case '(':{
			PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubParenthesisLeft), "(", 1);
				 }
				 break;
		case ')': {
			PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubParenthesisRight), ")", 1);
				  }
				  break;
		case ',': {
			PushList(list, MainLexType::MainSpace, int(SubSpace::SubComma), ",", 1);
				  }
				  break;
		case '.': {
			PushList(list, MainLexType::MainSpace, int(SubSpace::SubPoint), ".", 1);
				  }
				  break;
		case ':': {
			PushList(list, MainLexType::MainSymbol, int(SubSpace::SubPoint), ":", 1);
				  }
				  break;
		case '\"': {
			analyzeState = AnalyzeState::AnalyzeStringStart;
				   }
				   break;
		case '%': {
			PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubMod), "%", 1);
				  }
				  break;
		case '&': {
			if (i + 1 >= nLen){//处理异常情况
				return 0;
			}
			if ('&'== pszSrc[i + 1]) { // 与运算
				PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubAnd), "&&", 2);
				i++;
			} else {	//引用，用来支持指针
				PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubQuote), "&", 1);
			}
				  }
				  break;
		case '|': {
			if (i + 1 >= nLen){//处理异常情况
				return 0;
			}
			if ('|'== pszSrc[i + 1]) { // 与运算
				PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubOr), "||", 2);
				i++;
			}
				  }
				  break;
		case '!': {
			PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubNot), "!", 1);
				  }
				  break;
		case '=': {
			if (i + 1 >= nLen){//处理异常情况
				return 0;
			}
			if ('='== pszSrc[i + 1]) { // 等于
				PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubEqual), "==", 2);
				i++;
			} else {//赋值
				PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubAssignment), "=", 1);
			}
				  }
				  break;
		case '>': {
			if (i + 1 >= nLen){//处理异常情况
				return 0;
			}
			if ('='== pszSrc[i + 1]) { // 与运算
				PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubLargeEqual), ">=", 2);
				i++;
			} else {
				PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubLarge), ">", 1);
			}
				  }
				  break;
		case '<': {
			if (i + 1 >= nLen){//处理异常情况
				return 0;
			}
			if ('='== pszSrc[i + 1]) { // 与运算
				PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubLessEqual), "<=", 2);
				i++;
			} else {
				PushList(list, MainLexType::MainSymbol, int(SubOperationalSymbol::SubLess), "<", 1);
			}
				  }
				  break;
		default:
			break;
		}
		i++;
	}
	return 0;
}

int dump_lex(std::vector<LexItem> &listItem, const char *pszFilePath)
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