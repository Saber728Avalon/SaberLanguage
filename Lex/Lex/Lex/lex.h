#pragma once

#include <stdio.h>
#include <list>
#include "lex_header.h"

//�ʷ�����ʱ���״̬
enum  AnalyzeState
{
	AnalyzeUnknown, //��ʼ��״̬
	AnalyzeStringStart,//�ַ�����ʼ
	AnalyzeCommentForwardSlash ,//ע�Ϳ�ʼ//
	AnalyzeCommentSlashStar,//ע�Ϳ�ʼ/*

	AnalyzeCount
};

//�ʷ������Ľ����
struct LexItem
{
	MainLexType mainType; //������
	int subType;			//������
	std::string strInfo;			//��Ӧ���ַ������������Ϳ�Ϊ��
};

//�ʷ�����
int Lex(const char *pszSrc, int nLen, std::list<LexItem> &list); 

//��ʾ���
int Dump(std::list<LexItem> &list, const char *pszFilePath);