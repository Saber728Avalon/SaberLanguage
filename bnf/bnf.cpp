#include "bnf.h"
#include "bnf_header.h"


	long long int FileSize(FILE *pFile)
	{
#if defined(_WIN32) || defined(_WIN64)
#if defined(_USE_WIN32_API)
		uint64_t un64FileSize = 0;
		LARGE_INTEGER largeInteger = { 0 };
		BOOL bSuc = GetFileSizeEx(pFile, &largeInteger);
		if (!bSuc)
		{
			return 0;
		}
		un64FileSize = largeInteger.QuadPart;
#else
		long long int nCurPos = _ftelli64(pFile);
		_fseeki64(pFile, 0L, SEEK_END);
		long long int un64FileSize = _ftelli64(pFile);
		_fseeki64(pFile, nCurPos, SEEK_SET);
#endif
#else
		uint64_t nCurPos = ftello(pFile);
		fseeko(pFile, 0L, SEEK_END);
		uint64_t un64FileSize = ftello(pFile);
		fseeko(pFile, nCurPos, SEEK_SET);
#endif
		return un64FileSize;
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

int bnf_analyze(char *psz_info) {
   for (int i = 0; '\0' != psz_info[i]; i++) {
		
   }
}

int bnf(char *pszFilePath) {
	char buf[1024];
	FILE *pFile = fopen(pszFilePath, "r");
	if (nullptr == pFile) {
		return -1;
	}
	long long int n_size = FileSize(pFile);
	if (0 == n_size) {
		return 0;
	}
	//一行一行处理
	int n_pos = 0;
	char *p_buf = (char *)malloc(n_size);
	while(1) {
		int n_read= fread(p_buf + n_pos, 1, 1, pFile);
		if (0 == n_read) {
			break;
		}
		if ('\n' == p_buf[n_pos]) {
			*(p_buf + n_pos) = '\0';
		}
		n_pos++;
	}

}

int dump_bnf(std::vector<LexItem> &listItem, const char *pszFilePath)
{
	char buf[1024];
	FILE *pFile = fopen(pszFilePath, "wb");
	if (nullptr == pFile) {
		return 0;
	}
	for (auto iter = listItem.begin(); iter != listItem.end(); iter++)
	{
		sprintf(buf, "(%d, 0x%x, %s)\n", iter->mainType, iter->subType, iter->strInfo.c_str());
		fwrite(buf, 1, strlen(buf), pFile);
	}
	fclose(pFile);

	return 0;
}