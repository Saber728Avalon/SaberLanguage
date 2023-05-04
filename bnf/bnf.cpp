#include "bnf.h"
#include "bnf_header.h"
#include "bnf_lex.h"
#include <stdarg.h>

static FILE *g_pOutCppFile = nullptr; 
static FILE *g_pOutHFile = nullptr; 

//写cpp文件
void BNFprintfCPP(const char * _Format, ...) {
	char ch_buf[1024];
	va_list p;
	va_start(p, _Format);
	vsprintf(ch_buf, _Format, p);
	va_end(p);
	printf(ch_buf);
	fwrite(ch_buf, 1, strlen(ch_buf), g_pOutCppFile);
}

//写头文件
void BNFprintfH(const char * _Format, ...) {
	char ch_buf[1024];
	va_list p;
	va_start(p, _Format);
	vsprintf(ch_buf, _Format, p);
	va_end(p);
	printf(ch_buf);
	fwrite(ch_buf, 1, strlen(ch_buf), g_pOutHFile);
}

int GenerateCode(std::vector<BNFLexItem> &listInfo) {
	if (MainBNFLexType::MainBNFCoustom != listInfo[0].mainType
		&& MainBNFLexType::MainBNFSymbol != listInfo[1].mainType
		&& SubBNFSymbol::SubBNFSymbolDefinit != listInfo[1].subType) {
		printf("error: Not Left Error\n");
		for (int i = 0; i < listInfo.size(); i++) {
			printf("%s\n", listInfo[i].strInfo.c_str());
		}
	}

	BNFprintfCPP("int %s (std::vector<LexItem> &list, int n_start) { \n", listInfo[0].strInfo.c_str());
	BNFprintfH("int %s (std::vector<LexItem> &list, int n_start); \n", listInfo[0].strInfo.c_str());
	BNFprintfCPP(" int i = n_start; \n", listInfo[0].strInfo.c_str());
	for (int i = 2; i <listInfo.size(); i++) {
		if (MainBNFLexType::MainBNFChar == listInfo[i].mainType) { //这里是一个字符
			BNFprintfCPP("if(\"%s\" != list[i].strInfo) {return i;} \n", listInfo[i].strInfo.c_str());
			BNFprintfCPP("i++; \n");
		} else if (MainBNFLexType::MainBNFStr == listInfo[i].mainType) {//这里是一个字符串
			BNFprintfCPP("if(\"%s\" != list[i].strInfo) {return i;} \n", listInfo[i].strInfo.c_str());
			BNFprintfCPP("i++; \n");
		} else if (MainBNFLexType::MainBNFSymbol == listInfo[i].mainType
			&& SubBNFSymbol::SubBNFSymbolDefinit == listInfo[i].subType) { //或符号,标识二选一 

		} else if (MainBNFLexType::MainBNFCoustom == listInfo[i].mainType) {//用户标志，表示迭代
			BNFprintfCPP(" i = %s(list, i); \n", listInfo[i].strInfo.c_str());
		} else if (MainBNFLexType::MainBNFLineEnd == listInfo[i].mainType) { //一行结束，表示函数返回
			BNFprintfCPP(" return i; \n");
		} else if (MainBNFLexType::MainBNFSymbol == listInfo[i].mainType
			&& SubBNFSymbol::SubBNFSymbolParenthesisLeft == listInfo[i].subType) { //这里是要分组的
			BNFprintfCPP(" { \n");
		} else if (MainBNFLexType::MainBNFSymbol == listInfo[i].mainType
			&& SubBNFSymbol::SubBNFSymbolParenthesisRight == listInfo[i].subType) { //这里是要分组的
				BNFprintfCPP(" } \n");
		}
	}
	BNFprintfCPP("} \n\n\n\n\n");
	return 0;
}


/*
*
* <item0>::= '{' <item1> | <item2>
*
* int item0(lex lex, int pos) {
*  if ('{' != lex[pos]) {
*	 return 0;
* }
*  int n_item1 = item1(lex lex, int pos)	
* }
*/

int bnf_analyze(std::vector<BNFLexItem> &listInfo) {
	int i = 0;
	std::vector<BNFLexItem> listTmpInfo;
	for (int i = 0; i < listInfo.size(); i++) {
		if (MainBNFLexType::MainBNFLineEnd == listInfo[i].mainType) {
			if (!listTmpInfo.empty()) {
				listTmpInfo.push_back(listInfo[i]);
				GenerateCode(listTmpInfo);
				listTmpInfo.clear();
			}
			continue;
		}
		listTmpInfo.push_back(listInfo[i]);
	}
	return 0;
}

int bnf_file(char *pszFilePath) {

	return 0;
}

int bnf_info(char *pszInfo, int nLen, char *pszCppFilePath, char *pszHFilePath) {
	std::vector<BNFLexItem> listInfo;

	g_pOutCppFile= fopen(pszCppFilePath, "wb");
	if (nullptr == g_pOutCppFile) {
		return 0;
	}
	g_pOutHFile= fopen(pszHFilePath, "wb");
	if (nullptr == g_pOutHFile) {
		return 0;
	}
	//先进行词法分析
	bnf_lex(pszInfo, nLen, listInfo);
	//
	bnf_analyze(listInfo);
	return 0;
}

//int dump_bnf(std::vector<LexItem> &listItem, const char *pszFilePath)
//{
//	char buf[1024];
//	FILE *pFile = fopen(pszFilePath, "wb");
//	if (nullptr == pFile) {
//		return 0;
//	}
//	for (auto iter = listItem.begin(); iter != listItem.end(); iter++)
//	{
//		sprintf(buf, "(%d, 0x%x, %s)\n", iter->mainType, iter->subType, iter->strInfo.c_str());
//		fwrite(buf, 1, strlen(buf), pFile);
//	}
//	fclose(pFile);
//
//	return 0;
//}