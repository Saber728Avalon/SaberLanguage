#include "bnf.h"
#include "bnf_header.h"


#include <iostream>
#include "bnf_lex.h"

int main(int argc, char* argv[])
{
	//����BNF���﷨����
	char buf[1024];
	FILE *pFile = fopen("D:\\workspace\\SaberLanguage\\SaberLanguage\\source\\bnf.txt", "rb");
	if (nullptr == pFile) {
		return 0;
	}
	std::string strMsg;
	while (1) {
		int nRead = fread(buf, 1, 1024, pFile);
		if (0 == nRead) {
			break;
		}
		strMsg.append(buf, nRead);
	}
	std::vector<BNFLexItem> listInfo;
	bnf_lex(strMsg.c_str(), strMsg.length(), listInfo);
	//dump���
	dump_bnf_lex(listInfo, "D:\\workspace\\SaberLanguage\\SaberLanguage\\source\\bnf.txt.bnf_lex");


	//����BNF�Ĵʷ�����
	bnf_info((char *)strMsg.c_str(), strMsg.length(), "D:\\workspace\\SaberLanguage\\SaberLanguage\\source\\bnf.txt.cpp", "D:\\workspace\\SaberLanguage\\SaberLanguage\\source\\bnf.txt.h");
	return 0;
}

