#include "syntax.h"
#include "lex.h"

int main(int argc, char* argv[])
{
	char buf[1024];
	FILE *pFile = fopen("D:\\workspace\\SaberLanguage\\Lex\\source\\test.sl", "rb");
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
	
	//�﷨����
	binary_node node;
	node.p_left_node = NULL;
	node.p_right_node = NULL;
	syntax(listInfo, &node);

	dump_syntax(&node, "D:\\workspace\\SaberLanguage\\Lex\\source\\test.sl_syntax");
	return 0;
}

