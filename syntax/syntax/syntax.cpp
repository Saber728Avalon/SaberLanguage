// syntax.cpp : 定义控制台应用程序的入口点。
//
#include "syntax.h"

//判断是否是import
int check_is_import(LexItem *p_node) {
	if (MainLexType::MainKeyWord == p_node->mainType
		&& SubKeyWord::SubImport == p_node->subType) {
		return 1;
	}
	return 0;
}

//检查是否是space
int check_is_space(LexItem *p_node) {
	if (MainLexType::MainKeyWord == p_node->mainType
		&& SubKeyWord::SubSpace == p_node->subType) {
		return 1;
	}
	return 0;
}

//检查是否是函数
int check_is_func(LexItem *p_node) {
	if (MainLexType::MainKeyWord == p_node->mainType
		&& SubKeyWord::SubFunc == p_node->subType) {
		return 1;
	}
	return 0;
}

//检查是否是空间结束符号-分号
int check_is_semicolon(LexItem *p_node) {
	if (MainLexType::MainSpace == p_node->mainType
		&& SubSpace::SubSemicolon == p_node->subType) {
		return 1;
	}
	return 0;
}

//检查是否是空间结束符号 }
int check_is_right_brace(LexItem *p_node) {
	if (MainLexType::MainSpace == p_node->mainType
		&& SubSpace::SubBraceRight == p_node->subType) {
		return 1;
	}
	return 0;
}

//检查是否是空间结束符号 {
int check_is_left_brace(LexItem *p_node) {
	if (MainLexType::MainSpace == p_node->mainType
		&& SubSpace::SubBraceLeft == p_node->subType) {
		return 1;
	}
	return 0;
}


//语法分析
int syntax(std::vector<LexItem> &list, struct binary_node *p_node_root) {
	if (NULL == p_node_root) {
		return 0;
	}
	p_node_root->node_info.str_type = "program";
	struct binary_node *p_current_node = p_node_root;

	for (int i = 0; i < list.size(); i++) {
		if (check_is_import(&list[i])) {
			//添加到二叉树
			struct binary_node *p_node = new binary_node();//(struct binary_node *)malloc(sizeof(binary_node));
			p_node->node_info.str_type = "import_body";
			p_node->node_info.str_value = list[i].strInfo;
			p_current_node->p_left_node = p_node;
			p_current_node = p_node;
			//是import导入
			for (int j = i + 1; j < list.size(); j++) {
				//遇到了结束符号
				if (check_is_semicolon(&list[j])) {
					i = j + 1;//移动到分号的下一个
					break;
				}
				//添加到二叉树
				struct binary_node *p_node = (struct binary_node *)malloc(sizeof(binary_node));
				p_node->node_info.str_type = "import_body_item_path";
				p_node->node_info.str_value = list[j].strInfo;
				p_current_node->p_left_node = p_node;
				p_current_node = p_node;
			}
		} else if (check_is_func(&list[i])) {
			//添加到二叉树
			struct binary_node *p_node = (struct binary_node *)malloc(sizeof(binary_node));
			p_node->node_info.str_type = "function_list";
			p_node->node_info.str_value = list[i].strInfo;
			p_current_node->p_right_node = p_node;
			p_current_node = p_node;
			
			//是func定义的函数
			//首先将函数返回值参数等添加到二叉树
			for (int j = i + 1; j < list.size(); j++) {
				if (check_is_left_brace(&list[j])) {
					i = j + 1;
					break;
				}
				//添加到二叉树
				struct binary_node *p_node = (struct binary_node *)malloc(sizeof(binary_node));
				p_node->node_info.str_type = "function_body";
				p_node->node_info.str_value = list[j].strInfo;
				p_current_node->p_left_node = p_node;
				p_current_node = p_node;
			}
			//遇到了结束符号
			int left_brace = 1;
			for (int j = i + 1; j < list.size(); j++) {
				if (check_is_left_brace(&list[j])) {
					left_brace++;
				} else if (check_is_right_brace(&list[j])) {
					left_brace--;
				}
				//添加到二叉树
				struct binary_node *p_node = (struct binary_node *)malloc(sizeof(binary_node));
				p_node->node_info.str_type = "function_unit_lsit";
				p_node->node_info.str_value = list[j].strInfo;
				p_current_node->p_left_node = p_node;
				p_current_node = p_node;
				if (!left_brace) {
					break;
				}
			}
			
		}else {
		}
	}

}

//
int dump_format(FILE *p_file, struct binary_node *p_node_root, char chindented_char, int indented_count, char *p_buf_format, int n_buf_format_length) {
	int i = 0;
	for (i = 0; i < n_buf_format_length; i++) {
		p_buf_format[i] = chindented_char;
	}
	//后移一个位置
	i++;
	//左侧是子节点，右侧是兄弟节点
	if (p_node_root->p_left_node) { 
		p_buf_format[i] = '+';
	} else {
		p_buf_format[i] = '-';
	}
	//后移一个位置
	i++;
	p_buf_format[i] = chindented_char;

	//将类型复制过来
	i++;
	strncpy(p_buf_format + i, p_node_root->node_info.str_type.c_str(), p_node_root->node_info.str_type.length());
	
	//添加结束符号
	i++;
	p_buf_format[i] = '\n'; 
	fwrite(p_buf_format, 1, i, p_file);
	//前序遍历
	if (p_node_root->p_left_node) {
		dump_format(p_file, p_node_root->p_left_node, chindented_char, indented_count + 1, p_buf_format, n_buf_format_length);
	}
	//遍历右侧
	if (p_node_root->p_right_node) {
		dump_format(p_file, p_node_root->p_right_node, chindented_char, indented_count + 1, p_buf_format, n_buf_format_length);
	}
	return 0;
}

int dump_syntax(struct binary_node *p_node_root, char *p_file_path) {
	char *p_ch_buf = (char *)malloc(4*1024);
	FILE *pFile = fopen(p_file_path, "wb");
	if (nullptr == pFile) {
		return 0;
	}

	dump_format(pFile, p_node_root, ' ', 0, p_ch_buf, 4 * 1024);
	return 0;
}