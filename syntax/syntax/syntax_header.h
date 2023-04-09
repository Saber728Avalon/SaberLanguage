#include <stdio.h>
#include <iostream>

//ast树节点内容
struct syntex_node
{
	//数据的类型
	std::string str_type;
	//数据的值
	std::string str_value;
};