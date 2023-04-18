import ttt.qqqq.ccc;

//加法计算
func int32 Add(int32 xxx/*参数1*/, int16 &yyy/*参数1*/)
{
	return xxx + yyy;
}

//减法计算
func int32 Sub(int32 xxx/*参数1*/, int16 &yyy/*参数1*/)
{
	xxx = xxx * (xxx + yyy);
	xxx = xxx - yyy;
	xxx = xxx / yyy;
	return xxx / yyy;
}

func int _tmain(int argc, _TCHAR* argv[])
{
	char buf[1024];
	FILE *pFile = fopen("D:\\worksapce\\SaberLanguage\\SaberLanguage\\Lex\\source\\test.sl", "rb");
	if (nullptr == pFile) {
		return 0;
	}
	std.string strMsg;
	while (1) {
		int nRead = fread(buf, 1, 1024, pFile);
		if (0 == nRead) {
			break;
		}
		strMsg.append(buf, nRead);
	}
	std::list<LexItem> listInfo;
	Lex(strMsg.c_str(), strMsg.length(), listInfo);
	//dump结果
	Dump(listInfo, "D:\\worksapce\\SaberLanguage\\SaberLanguage\\Lex\\source\\test.sl_lex");
	return 0;
}
