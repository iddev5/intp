#ifndef INTP_MAIN_H
#define INTP_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#include "../depends/stb_ds.h"

enum token_type {
    HEX, BIN, NUM,

    EOL, LBRAC, RBRAC, LPAREN, RPAREN,
    PLUS, MINUS, MULTI, DIV, MOD, POW,
    GRT, LES, EQU, SEMI, COL, HASH,

    STRING, IDENTIFIER,

	KWD_AND, KWD_BREAK, KWD_CONTINUE, KWD_DO,
    KWD_ELSE, KWD_FALSE, KWD_FOR, KWD_IF,
    KWD_IN, KWD_IMPORT, KWD_OR, KWD_RETURN,
    KWD_TRUE, KWD_WHILE
};

enum data_type {
    INT, REAL, STR, OTH
};

#define class typedef struct

/*
 *----------Structs-----------
 */
class intp_data {
    char *name;
    uint8_t  type;
    uint32_t scope;
    
    union {
        int64_t inn;
        double  fnn;
        char *str;
        void *oth;
    } val;

} intp_data;

class intp_src_buf {
	uint32_t line, col;
    char *data, *tok;
	int32_t type;

    union {
        int64_t inn;
        double  fnn;
    } val;
} intp_src_buf;

class intp_info {
	intp_src_buf *buf;
    uint32_t scope_count;
    intp_data **objs;

} intp_info;

/*
 *----------Lexer-------------
 */
int intp_lex(intp_src_buf *buf);

/*
 *----------Parser------------
 */
intp_data *intp_parse(intp_src_buf *buf, intp_info *info);

/*
 *----------Logging-----------
 */
void intp_warn(intp_src_buf *buf, char *str);
int  intp_error(intp_src_buf *buf, char *str);

/*
 *----------Data Types--------
 */
intp_data *new_data(const char *name, int type, void *value);
intp_data *intp_get_data(intp_info *info, char *name);
void intp_set_data(intp_info *info, const char* name, int type, void *value);

/*
 *----------Main--------------
 */
int  intp_init(intp_info *info);
void intp_free(intp_info *info);

void intp_string(intp_info *info , char *str);
void intp_file(intp_info *info, char *fn);

#endif
