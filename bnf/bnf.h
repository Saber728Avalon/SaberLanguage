#pragma once

#include <stdio.h>
#include <vector>
#include "bnf_lex_header.h"

////�ʷ�����ʱ���״̬
//enum  AnalyzeState
//{
//	AnalyzeUnknown, //��ʼ��״̬
//	AnalyzeStringStart,//�ַ�����ʼ
//	AnalyzeCommentForwardSlash ,//ע�Ϳ�ʼ//
//	AnalyzeCommentSlashStar,//ע�Ϳ�ʼ/*
//
//	AnalyzeCount
//};
//
////�ʷ������Ľ����
//struct LexItem
//{
//	MainBNFLexType mainType; //������
//	int subType;			//������
//	std::string strInfo;			//��Ӧ���ַ������������Ϳ�Ϊ��
//};
//
//����BNF�ļ�
int bnf_file(char *pszFilePath); 
//����BNF�ַ���
int bnf_info(char *pszInfo, int nLen, char *pszCppFilePath, char *pszHFilePath); 
//
////��ʾ���
//int dump_lex(std::vector<LexItem> &list, const char *pszFilePath);