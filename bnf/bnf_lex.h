#include <stdio.h>
#include <vector>
#include "bnf_lex_header.h"

//词法分析时候的状态
enum  AnalyzeState
{
	AnalyzeUnknown, //初始化状态
	AnalyzeStringStart,//字符串开始
	AnalyzeCommentForwardSlash ,//注释开始//
	AnalyzeCommentSlashStar,//注释开始/*

	AnalyzeCount
};

//词法分析的结果项
struct BNFLexItem
{
	MainBNFLexType mainType; //主类型
	int subType;			//子类型
	std::string strInfo;			//对应的字符串，根据类型可为空
};

//词法分析
int bnf_lex(const char *pszSrc, int nLen, std::vector<BNFLexItem> &list); 

//显示结果
int dump_bnf_lex(std::vector<BNFLexItem> &list, const char *pszFilePath);