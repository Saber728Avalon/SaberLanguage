#pragma once

#include <stdio.h>
#include <iostream>

//ast树节点内容
class syntex_node
{
public:
	//数据的类型
	std::string str_type;
	//数据的值
	std::string str_value;
};

//ast 语法树节点
class binary_node
{
public:
	binary_node *p_left_node;
	binary_node *p_right_node;
	syntex_node node_info;
};