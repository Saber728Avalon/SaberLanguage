// syntax.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "syntax.h"

//�ж��Ƿ���import
int check_is_import(LexItem *p_node) {
	if (MainLexType::MainKeyWord == p_node->mainType
		&& SubKeyWord::SubImport == p_node->subType) {
		return 1;
	}
	return 0;
}

//����Ƿ���space
int check_is_space(LexItem *p_node) {
	if (MainLexType::MainKeyWord == p_node->mainType
		&& SubKeyWord::SubSpace == p_node->subType) {
		return 1;
	}
	return 0;
}

//����Ƿ��Ǻ���
int check_is_func(LexItem *p_node) {
	if (MainLexType::MainKeyWord == p_node->mainType
		&& SubKeyWord::SubFunc == p_node->subType) {
		return 1;
	}
	return 0;
}


//�﷨����
int Lex(std::vector<LexItem> &list, struct binary_node *p_node_root) {
	if (NULL == p_node_root) {
		return 0;
	}
	p_node_root->node_info.str_type = "program";

	LexItem *p_current = &(list[0]);
	LexItem *p_next = &(list[1]);


}

