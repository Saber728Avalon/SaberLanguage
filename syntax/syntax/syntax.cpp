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

//����Ƿ��ǿռ��������-�ֺ�
int check_is_semicolon(LexItem *p_node) {
	if (MainLexType::MainSpace == p_node->mainType
		&& SubSpace::SubSemicolon == p_node->subType) {
		return 1;
	}
	return 0;
}

//����Ƿ��ǿռ�������� }
int check_is_right_brace(LexItem *p_node) {
	if (MainLexType::MainSpace == p_node->mainType
		&& SubSpace::SubBraceRight == p_node->subType) {
		return 1;
	}
	return 0;
}

//����Ƿ��ǿռ�������� {
int check_is_left_brace(LexItem *p_node) {
	if (MainLexType::MainSpace == p_node->mainType
		&& SubSpace::SubBraceLeft == p_node->subType) {
		return 1;
	}
	return 0;
}


//�﷨����
int syntax(std::vector<LexItem> &list, struct binary_node *p_node_root) {
	if (NULL == p_node_root) {
		return 0;
	}
	p_node_root->node_info.str_type = "program";
	struct binary_node *p_current_node = p_node_root;

	for (int i = 0; i < list.size(); i++) {
		if (check_is_import(&list[i])) {
			//��ӵ�������
			struct binary_node *p_node = new binary_node();//(struct binary_node *)malloc(sizeof(binary_node));
			p_node->node_info.str_type = "import_body";
			p_node->node_info.str_value = list[i].strInfo;
			p_current_node->p_left_node = p_node;
			p_current_node = p_node;
			//��import����
			for (int j = i + 1; j < list.size(); j++) {
				//�����˽�������
				if (check_is_semicolon(&list[j])) {
					i = j + 1;//�ƶ����ֺŵ���һ��
					break;
				}
				//��ӵ�������
				struct binary_node *p_node = (struct binary_node *)malloc(sizeof(binary_node));
				p_node->node_info.str_type = "import_body_item_path";
				p_node->node_info.str_value = list[j].strInfo;
				p_current_node->p_left_node = p_node;
				p_current_node = p_node;
			}
		} else if (check_is_func(&list[i])) {
			//��ӵ�������
			struct binary_node *p_node = (struct binary_node *)malloc(sizeof(binary_node));
			p_node->node_info.str_type = "function_list";
			p_node->node_info.str_value = list[i].strInfo;
			p_current_node->p_right_node = p_node;
			p_current_node = p_node;
			
			//��func����ĺ���
			//���Ƚ���������ֵ��������ӵ�������
			for (int j = i + 1; j < list.size(); j++) {
				if (check_is_left_brace(&list[j])) {
					i = j + 1;
					break;
				}
				//��ӵ�������
				struct binary_node *p_node = (struct binary_node *)malloc(sizeof(binary_node));
				p_node->node_info.str_type = "function_body";
				p_node->node_info.str_value = list[j].strInfo;
				p_current_node->p_left_node = p_node;
				p_current_node = p_node;
			}
			//�����˽�������
			int left_brace = 1;
			for (int j = i + 1; j < list.size(); j++) {
				if (check_is_left_brace(&list[j])) {
					left_brace++;
				} else if (check_is_right_brace(&list[j])) {
					left_brace--;
				}
				//��ӵ�������
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
	//����һ��λ��
	i++;
	//������ӽڵ㣬�Ҳ����ֵܽڵ�
	if (p_node_root->p_left_node) { 
		p_buf_format[i] = '+';
	} else {
		p_buf_format[i] = '-';
	}
	//����һ��λ��
	i++;
	p_buf_format[i] = chindented_char;

	//�����͸��ƹ���
	i++;
	strncpy(p_buf_format + i, p_node_root->node_info.str_type.c_str(), p_node_root->node_info.str_type.length());
	
	//��ӽ�������
	i++;
	p_buf_format[i] = '\n'; 
	fwrite(p_buf_format, 1, i, p_file);
	//ǰ�����
	if (p_node_root->p_left_node) {
		dump_format(p_file, p_node_root->p_left_node, chindented_char, indented_count + 1, p_buf_format, n_buf_format_length);
	}
	//�����Ҳ�
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