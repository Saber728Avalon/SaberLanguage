#pragma once
#include <stdio.h>
#include <iostream>
#include "syntax_header.h"




//增加左节点,返回值，新增的节点位置
binary_node * add_left_node(binary_node *p_current_node, std::string str_type, std::string str_value);

//增加右节点，返回值，新增的节点位置
binary_node * add_right_node(binary_node *p_current_node, std::string str_type, std::string str_value);

//删除节点
int del_node(binary_node *root, binary_node &node);

//dump输出节点信息
int Dump(binary_node *root, const char *pszFilePath);
