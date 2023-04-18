// syntax.cpp : 定义控制台应用程序的入口点。
//
#include "syntax.h"
#include "binary_tree.h"

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


int next(std::vector<LexItem> &list, int n_pos, binary_node *node) {
	//遇到了分号结束符
	if (check_is_semicolon(&list[n_pos])) {
		n_pos++;
		return n_pos;
	}
	//遇到了右花括号结束符
	if (check_is_right_brace(&list[n_pos])) {
		n_pos++;
		return n_pos;
	}
	return 0;
}

//语法分析
int syntax(std::vector<LexItem> &list, binary_node *p_node_root) {
	if (NULL == p_node_root) {
		return 0;
	}
	p_node_root->node_info.str_type = "program";
	struct binary_node *p_group_node = p_node_root;
	struct binary_node *p_tmp_node = p_node_root;

	for (int i = 0; i < list.size(); i++) {
		if (check_is_import(&list[i])) {
			//添加到二叉树
			p_node_root = add_left_node(p_group_node, "import_body", list[i].strInfo);
			std::string strTmp;
			//是import导入
			for (int j = i + 1; j < list.size(); j++) {
				//遇到了结束符号
				if (check_is_semicolon(&list[j])) {
					i = j;//移动到新位置
					break;
				}
				strTmp += list[j].strInfo;
			}
			//添加到二叉树
			p_node_root = add_left_node(p_node_root, "import_body_item_path", strTmp);
		} else if (check_is_func(&list[i])) {
			//添加到二叉树
			p_node_root = add_right_node(p_group_node, "function_list", list[i].strInfo);
			//是func定义的函数
			//首先将函数返回值参数等添加到二叉树
			std::string strTmp;
			for (int j = i + 1; j < list.size(); j++) {
				if (check_is_left_brace(&list[j])) {
					i = j;//移动到新位置
					break;
				}
				strTmp += list[j].strInfo;
			}
			//添加到二叉树
			p_node_root = add_left_node(p_node_root, "function_declare", strTmp);
			//遇到了结束符号
			int left_brace = 1; strTmp.clear();
			for (int j = i + 1; j < list.size(); j++) {
				if (check_is_left_brace(&list[j])) {
					strTmp.clear();
					left_brace++;
				} else if (check_is_right_brace(&list[j])) {
					//添加到二叉树
					p_node_root = add_left_node(p_node_root, "function_unit_lsit", list[i].strInfo);
					left_brace--;
				}
				strTmp += list[j].strInfo;
			}
			if (!left_brace) {
				break;
			}

		}else {
		}
	}
	return 0;
}

// 连接字符串
char * buf_append_str(char *p_buf_format, int n_buf_format_length, const char *p_append, int n_append_length) {
	int i = 0;

	if (n_append_length > n_buf_format_length) {
		return NULL;
	}
	while(i < n_append_length) {
		p_buf_format[i] = p_append[i];
		i++;
	}
	return p_buf_format + n_append_length;
}

char * buf_append_ch(char *p_buf_format, int n_buf_format_length, char ch, int count) {
	int i = 0;

	if (count > n_buf_format_length) {
		return NULL;
	}
	while(i < count) {
		p_buf_format[i] = ch;
		i++;
	}
	return p_buf_format + i;
}

//
int dump_format(FILE *p_file, binary_node *p_node_root, char indented_char, int indented_count, char *p_buf_format, int n_buf_format_length) {
	int i = 0;
	char * buf_tmp = p_buf_format;
	//首先添加一个空格
	buf_tmp = buf_append_ch(buf_tmp, n_buf_format_length, ' ', 1);
	//添加缩进
	buf_tmp = buf_append_ch(buf_tmp, n_buf_format_length, indented_char, indented_count);
	//后移一个位置
	i++;
	//左侧是子节点，右侧是兄弟节点
	if (p_node_root->p_left_node) { 
		buf_tmp = buf_append_ch(buf_tmp, n_buf_format_length, '+', 1);
	} else {
		buf_tmp = buf_append_ch(buf_tmp, n_buf_format_length, '-', 1);
	}
	//后移一个位置
	buf_tmp = buf_append_ch(buf_tmp, n_buf_format_length, ' ', 1);

	//将类型复制过来
	buf_tmp = buf_append_str(buf_tmp, n_buf_format_length, p_node_root->node_info.str_type.c_str(), p_node_root->node_info.str_type.length());
	//类型与值的分割符号
	buf_tmp = buf_append_str(buf_tmp, n_buf_format_length, " <==> ", 6);
	buf_tmp = buf_append_str(buf_tmp, n_buf_format_length, p_node_root->node_info.str_value.c_str(), p_node_root->node_info.str_value.length());
	//添加结束符号
	buf_tmp = buf_append_str(buf_tmp, n_buf_format_length, "\r\n", 2);
	//写入类型
	int write = fwrite(p_buf_format, 1, buf_tmp - p_buf_format, p_file);

	//前序遍历
	if (p_node_root->p_left_node) {
		dump_format(p_file, p_node_root->p_left_node, indented_char, indented_count + 1, p_buf_format, n_buf_format_length);
	}
	//遍历右侧
	if (p_node_root->p_right_node) {
		dump_format(p_file, p_node_root->p_right_node, indented_char, indented_count + 1, p_buf_format, n_buf_format_length);
	}
	return 0;
}

int dump_syntax(binary_node *p_node_root, char *p_file_path) {
	char *p_ch_buf = (char *)malloc(4*1024);
	FILE *pFile = fopen(p_file_path, "wb");
	if (nullptr == pFile) {
		return 0;
	}

	dump_format(pFile, p_node_root, ' ', 0, p_ch_buf, 4 * 1024);
	fflush(pFile);
	fclose(pFile);
	return 0;
}