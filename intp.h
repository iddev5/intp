#ifndef INTP_H
#define INTP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////
//----------Utilities---------
//////////////////////////////

#define SYMBOL_COUNT 28

static char intp__lex_symbols[SYMBOL_COUNT] = {
    '~', '!', '@', '#',
    '%', '^', '&', '*',
    '(', ')', '-', '_',
    '+', '=', '{', '}',
    '[', ']', '|', '\\',
    ':', ';', '\"', '\'',
    '<', '>', '?', '/'
};

static int intp_is_space(char c) {
    return (c == ' ');
}

static int intp_is_sym(char c) {
    for(int i = 0; i < SYMBOL_COUNT; i++) {
        if (c == intp__lex_symbols[i]) return 1;
    }
    return 0;
}

static int intp_is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static int intp_is_num(char c) {
    return (c >= '0' && c <= '9');
}

static int intp_is_id(char c) {
    return intp_is_alpha(c) || c == '_';
}

/*
//----------Utilities---------
int intp_is_space(char c);
int intp_is_alpha(char c);
int intp_is_num(char c);
int intp_is_id(char c);
*/

//----------Enums-------------
enum intp__token_type {
    hex,
    bin,
    num,
    al,

    op_add,
    op_sub,
    op_mul,
    op_div,
    op_inc,
    op_dec
};

//----------Structs-----------
typedef struct {
    char *data;
    char *tok;
    char *word;
    /**<----->*/
} intp_info;

//----------Main--------------
int intp_init(intp_info *info);
int intp_free(intp_info *info);

void intp_string(intp_info *info , char *str);
void intp_file(intp_info *info, char *fn);

#endif
