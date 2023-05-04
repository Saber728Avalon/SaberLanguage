#pragma once

#include <stdio.h>
#include <vector>
#include "bnf_lex_header.h"

////词法分析时候的状态
//enum  AnalyzeState
//{
//	AnalyzeUnknown, //初始化状态
//	AnalyzeStringStart,//字符串开始
//	AnalyzeCommentForwardSlash ,//注释开始//
//	AnalyzeCommentSlashStar,//注释开始/*
//
//	AnalyzeCount
//};
//
////词法分析的结果项
//struct LexItem
//{
//	MainBNFLexType mainType; //主类型
//	int subType;			//子类型
//	std::string strInfo;			//对应的字符串，根据类型可为空
//};
//
//解析BNF文件
int bnf_file(char *pszFilePath); 
//解析BNF字符串
int bnf_info(char *pszInfo, int nLen, char *pszCppFilePath, char *pszHFilePath); 
//
////显示结果
//int dump_lex(std::vector<LexItem> &list, const char *pszFilePath);