#include <stdio.h>
#include "syntax_header.h"



//���ӽڵ�
int add_node(struct binary_node *root, struct binary_node &node);

//ɾ���ڵ�
int del_node(struct binary_node *root, struct binary_node &node);

//dump����ڵ���Ϣ
int Dump(struct binary_node *root, const char *pszFilePath);
