#pragma once

#include <stdio.h>
#include <iostream>

//ast���ڵ�����
class syntex_node
{
public:
	//���ݵ�����
	std::string str_type;
	//���ݵ�ֵ
	std::string str_value;
};

//ast �﷨���ڵ�
class binary_node
{
public:
	binary_node *p_left_node;
	binary_node *p_right_node;
	syntex_node node_info;
};