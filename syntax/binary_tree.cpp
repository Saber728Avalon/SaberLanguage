#include "binary_tree.h"

binary_node *  add_left_node(binary_node *p_current_node, std::string str_type, std::string str_value) {
	binary_node *p_node = new binary_node;//(struct binary_node *)malloc(sizeof(binary_node));
	if (NULL == p_node) {
		return NULL;
	}
	p_node->node_info.str_type = str_type;
	p_node->node_info.str_value = str_value;
	p_node->p_left_node = NULL;
	p_node->p_right_node = NULL;
	p_current_node->p_left_node = p_node;
	return p_node;
}

binary_node *  add_right_node(binary_node *p_current_node, std::string str_type, std::string str_value) {
	binary_node *p_node = new binary_node();//(struct binary_node *)malloc(sizeof(binary_node));
	if (NULL == p_node) {
		return NULL;
	}
	p_node->node_info.str_type = str_type;
	p_node->node_info.str_value = str_value;
	p_node->p_left_node = NULL;
	p_node->p_right_node = NULL;
	p_current_node->p_right_node = p_node;
	return p_node;
}

