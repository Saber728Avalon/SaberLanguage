#pragma once
#include <stdio.h>
#include <iostream>
#include "syntax_header.h"




//������ڵ�,����ֵ�������Ľڵ�λ��
binary_node * add_left_node(binary_node *p_current_node, std::string str_type, std::string str_value);

//�����ҽڵ㣬����ֵ�������Ľڵ�λ��
binary_node * add_right_node(binary_node *p_current_node, std::string str_type, std::string str_value);

//ɾ���ڵ�
int del_node(binary_node *root, binary_node &node);

//dump����ڵ���Ϣ
int Dump(binary_node *root, const char *pszFilePath);
