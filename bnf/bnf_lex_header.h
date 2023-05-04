#pragma once


//������
enum MainBNFLexType
{
	MainBNFKeyWord = 0x1,//�ؼ���
	MainBNFSymbol, //�������
	MainBNFChar, //һ���ַ�
	MainBNFStr, //һ���ַ���
	MainBNFCoustom, //�Զ���item
	MainBNFLineEnd, //һ�н�������

	MainBNFCount
};


enum SubBNFKeyWord
{
	SubBNFKEYDoubleQuote = 0x1000, //˫����

	SubBNFKEYCount
};

//С����,�ؼ��ֶ�Ӧ���ַ���
static char* SubBNFKeyWordStr[] = 
{
	"double_quote"
};

enum SubBNFSymbol {
	SubBNFSymbolLess = 0x2000, // <
	SubBNFSymbolLarge, // >
	SubBNFSymbolBracketsLeft, //[
	SubBNFSymbolBracketsRight, //]
	SubBNFSymbolBraceLeft, // {
	SubBNFSymbolBraceRight, // }
	SubBNFSymbolParenthesisLeft, // (
	SubBNFSymbolParenthesisRight, // )
	SubBNFSymbolOr, // |
	SubBNFSymbolDefinit, //::=

	SubBNFSymbolCount
};