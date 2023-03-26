// Lex.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "lex.h"

int _tmain(int argc, _TCHAR* argv[])
{
	char buf[1024];
	FILE *pFile = fopen("D:\\worksapce\\SaberLanguage\\SaberLanguage\\Lex\\source\\test.sl", "rb");
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
	std::list<LexItem> listInfo;
	Lex(strMsg.c_str(), strMsg.length(), listInfo);
	//dump���
	Dump(listInfo, "D:\\worksapce\\SaberLanguage\\SaberLanguage\\Lex\\source\\test.sl_lex");
	return 0;
}
