#pragma once 

#include "lex.h"
#include "syntax_header.h"

//ast Óï·¨Ê÷½Úµã
struct binary_node
{
	struct binary_node *p_left_node;
	struct binary_node *p_right_node;
	struct syntex_node node_info;
}

static const char* s_bnf_item[] = {
	"program"
	, "import_body"
	, "program_body"
	, "import_body_item"
	, "import_body_item_path"
	, "identifier"
	, "space_name"
	, "variable_declare_and_code"
	, "variable_declare"
	, "code_gather"
	, "declare_type"
	, "inner_declare_type"
	, "custom_declare_type"
	, "int8"
	, "int16"
	, "int32"
	, "int64"
	, "uint8"
	, "uint16"
	, "uint32"
	, "uint64"
	, "double"
	, "struct_enum_definition"
	, "struct_enum_declare_list"
	, "function_implement_list"
	, "code_gather"
	, "function_list"
	, "function_declare_list"
	, "function_declare"
	, "function_parameter_list"
	, "function_body"
	, "function_unit_lsit"
	, "function_unit"
	, "expression"
	, "jump_expression"
	, "asignment_expression"
	, "condition_expression"
	, "logical_expression"
	, "logical_or_expression"
	, "logical_and_expression"
	, "logical_not_expression"
};