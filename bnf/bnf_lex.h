#include <stdio.h>
#include <vector>
#include "bnf_lex_header.h"

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
struct BNFLexItem
{
	MainBNFLexType mainType; //������
	int subType;			//������
	std::string strInfo;			//��Ӧ���ַ������������Ϳ�Ϊ��
};

//�ʷ�����
int bnf_lex(const char *pszSrc, int nLen, std::vector<BNFLexItem> &list); 

//��ʾ���
int dump_bnf_lex(std::vector<BNFLexItem> &list, const char *pszFilePath);