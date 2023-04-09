//ע�͹��ɣ�ע��ʹ��//���� /**/
#pragma once

//������
enum MainLexType
{
	MainKeyWord = 0x1,//�ؼ���
	MainSpace,  //�ռ�֮��ķ���
	MainWord,   //�����
	MainSymbol, //�������
	MainCustom, //�Զ�������

	MainCount
};

//С����,�ؼ���
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
//С����,�ؼ��ֶ�Ӧ���ַ���
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

//С���ţ��ռ����
enum SubSpace
{
	SubBraceLeft=0x2000, // {
	SubBraceRight, //}
	SubSemicolon,  // ;
	SubPoint,  //.
	SubComma, //,
	

	SubSpaceCount
};

//С����,�������
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
	SubQuote,		// &����
	SubEqual,		// ==
	SubLarge,		// >
	SubLargeEqual,	// >=
	SubLess,		// <
	SubLessEqual,	// <=


	SubOperationalSymbolCount
};

//С����,�Զ������
enum SubCustom
{
	SubString, //�ַ���
	SubParam,//�Զ���Ĳ���


	SubCustomCount
};
