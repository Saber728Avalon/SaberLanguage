// Lex.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "lex.h"

int _tmain(int argc, _TCHAR* argv[])
{
	char buf[1024];
	FILE *pFile = fopen("D:\\workspace\\SaberLanguage\\SaberLanguage\\Lex\\source\\test.sl", "rb");
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
	std::vector<LexItem> listInfo;
	Lex(strMsg.c_str(), strMsg.length(), listInfo);
	//dump结果
	dump_lex(listInfo, "D:\\workspace\\SaberLanguage\\SaberLanguage\\Lex\\source\\test.sl_lex");
	return 0;
}

