//注释构成，注释使用//或者 /**/
#pragma once

//大类型
enum MainLexType
{
	MainKeyWord = 0x1,//关键字
	MainSpace,  //空间之类的符号
	MainWord,   //词类别
	MainSymbol, //运算符号
	MainCustom, //自定义类型

	MainCount
};

//小类型,关键字
enum SubKeyWord
{
	SubI8=0x1000 ,   //8bit char
	SubI16       ,   //16bit char
	SubI132      ,   //32bit char
	SubI164      ,   //64bit char
	SubU8        ,   //8bit char
	SubU16       ,   //16bit char
	SubU32       ,   //32bit char
	SubU64       ,   //64bit char
	SubFor		 ,	//for
	SubIf		,		//if
	SubElse		,		//else
	SubWhile	,		//while
	SubReturn	,		//return
	SubImport	,		//import
	SubSpace	,		//space
	SubInterface,		//interface
	SubStruct	,		//struct
	SubAlign	,		//align
	SubFunc		,		//func


	SubKeyWordCount
};
//小类型,关键字对应的字符串
static char* SubKeyWordStr[] = 
{
	"int8",
	"int16",
	"int32",
	"int64",
	"uint8",
	"uint16",
	"uint32",
	"uint64",
	"for",
	"if",
	"else",
	"while",
	"return",
	"import",
	"space",
	"interface",
	"struct",
	"align",
	"func",

	"",
};

//小符号，空间符号
enum SubSpace
{
	SubBraceLeft=0x2000, // {
	SubBraceRight, //}
	SubSemicolon,  // ;
	SubPoint,  //.
	SubComma, //,
	

	SubSpaceCount
};

//小类型,运算符号
enum SubOperationalSymbol
{
	SubParenthesisLeft=0x3000, //(
	SubParenthesisRight, //)
	SubBracketsLeft,		//[
	SubBracketsRight,		//]
	SubAdd		,//+
	SubSub,			// -
	SubMul,			// *
	SubDiv,			// /
	SubMod,			// %
	SubAssignment, //=
	SubAnd,			// &&
	SubOr,			// ||
	SubNot,			// !
	SubQuote,		// &引用
	SubEqual,		// ==
	SubLarge,		// >
	SubLargeEqual,	// >=
	SubLess,		// <
	SubLessEqual,	// <=


	SubOperationalSymbolCount
};

//小类型,自定义符号
enum SubCustom
{
	SubString, //字符串
	SubParam,//自定义的参数


	SubCustomCount
};
