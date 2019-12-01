#ifndef INTP_H
#define INTP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "stb/stb_ds.h"

//----------Enums-------------
enum intp__token_type {
    hex,
    bin,
    num,
    alpha,
    op_add,
    op_sub,
    op_mul,
    op_div,
    op_inc,
    op_dec
};

//----------Structs-----------
struct _dataobject {
    char *key;
    void *value;
    uint32_t scope_number;
};

typedef struct {
	unsigned int line, col;
	
    char *data;
    char *tok;
    char *word;

    uint32_t scope_count;

    struct _dataobject *objs;
} intp_info;

//----------Lexer-------------
int _lex(intp_info *info);

//----------Parser------------
void _parse(intp_info *info);

//----------Logging-----------
void intp_warn(intp_info *info, char *str);
int intp_error(intp_info *info, char *str);

//----------Data Types--------
void*intp_get_data(intp_info *info, char *name);
void intp_set_data(intp_info *info, const char* name, void *value, bool is_constant);

//----------Main--------------
int intp_init(intp_info *info);
void intp_free(intp_info *info);

void intp_string(intp_info *info , char *str);
void intp_file(intp_info *info, char *fn);

#endif
