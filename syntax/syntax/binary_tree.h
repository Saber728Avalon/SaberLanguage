#include <stdio.h>
#include "syntax_header.h"



//增加节点
int add_node(struct binary_node *root, struct binary_node &node);

//删除节点
int del_node(struct binary_node *root, struct binary_node &node);

//dump输出节点信息
int Dump(struct binary_node *root, const char *pszFilePath);
