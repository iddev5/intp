#ifndef INTP_H
#define INTP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#include "stb/stb_ds.h"
#include "sds/sds.h"

#define class typedef struct

//----------Enums-------------
enum _token_type {
	// Different types of numbers [0+i]
	// 0
    hex=0,
    bin,
    num,
    // 2

	// Keywords [10+i]
	// 10
	kwd_break=10,
	kwd_case,
	kwd_class,
	kwd_const,
	kwd_continue,
	kwd_define,
	kwd_delete,
	kwd_do,
	kwd_else,
	kwd_for,
	kwd_if,
	kwd_in,          
	kwd_is, 
	kwd_import,   
	kwd_int,      
	kwd_pass,
	kwd_real, 
	kwd_string,   
	kwd_return,   
	kwd_switch,	
	kwd_var,
	kwd_void,    
	kwd_while,
	// 32

	// 33
    ident,     // Any identifier
	string,
	// 34

	operator,

    // Types of operators
    // 40
    op_add=40,
    op_sub,
    op_mul,
    op_div,
    op_inc,
    op_dec,
    // 45

	semicol=70
};

//----------Structs-----------
class {
    char *key;
    void *value;
    uint32_t scope_number;
} intp_dataobject;

class {
	unsigned int line, col;
    char *data, *tok;
	int type;
} intp_src_buf;

class {
	intp_src_buf *buf;
    uint32_t scope_count;
    intp_dataobject *objs;

} intp_info;

//----------Lexer-------------
int intp_lex(intp_src_buf *buf);

//----------Parser------------
void*intp_eval(intp_info *info);
void intp_parse(intp_info *info);

//----------Logging-----------
void intp_warn(intp_src_buf *buf, char *str);
int intp_error(intp_src_buf *buf, char *str);

//----------Data Types--------
void*intp_get_data(intp_info *info, char *name);
void intp_set_data(intp_info *info, const char* name, void *value, bool is_constant);

//----------Main--------------
int intp_init(intp_info *info);
void intp_free(intp_info *info);

void intp_string(intp_info *info , char *str);
void intp_file(intp_info *info, char *fn);

#endif
