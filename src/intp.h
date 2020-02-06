#ifndef INTP_MAIN_H
#define INTP_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#include "../depends/stb_ds.h"

#define class typedef struct

/*
 *----------Structs-----------
 */
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

/*
 *----------Lexer-------------
 */
int intp_lex(intp_src_buf *buf);

/*
 *----------Parser------------
 */
void*intp_eval(intp_info *info);
void intp_parse(intp_info *info);

/*
 *----------Logging-----------
 */
void intp_warn(intp_src_buf *buf, char *str);
int intp_error(intp_src_buf *buf, char *str);

/*
 *----------Data Types--------
 */
void*intp_get_data(intp_info *info, char *name);
void intp_set_data(intp_info *info, const char* name, void *value, bool is_constant);

/*
 *----------Main--------------
 */
int intp_init(intp_info *info);
void intp_free(intp_info *info);

void intp_string(intp_info *info , char *str);
void intp_file(intp_info *info, char *fn);

#endif
