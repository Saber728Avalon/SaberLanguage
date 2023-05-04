#pragma once


//大类型
enum MainBNFLexType
{
	MainBNFKeyWord = 0x1,//关键字
	MainBNFSymbol, //运算符号
	MainBNFChar, //一个字符
	MainBNFStr, //一个字符串
	MainBNFCoustom, //自定义item
	MainBNFLineEnd, //一行结束符号

	MainBNFCount
};


enum SubBNFKeyWord
{
	SubBNFKEYDoubleQuote = 0x1000, //双引号

	SubBNFKEYCount
};

//小类型,关键字对应的字符串
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