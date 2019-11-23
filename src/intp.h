#ifndef INTP_H
#define INTP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "stb/stb_ds.h"

#define SYMBOL_COUNT 28

// Right now only including required sumbols. May add more soon.
static char _lex_symbols[SYMBOL_COUNT] = {
    '~', '!', '@', '#',
    '%', '^', '&', '*',
    '(', ')', '-', '_',
    '+', '=', '{', '}',
    '[', ']', '|', '\\',
    ':', ';', '\"', '\'',
    '<', '>', '?', '/'
};

//----------Utilities---------

static int intp_is_space(char c) {
    return (c == ' ');
}

static int intp_is_sym(char c) {
    for(int i = 0; i < SYMBOL_COUNT; i++) {
        if (c == _lex_symbols[i]) return 1;
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
    char *data;
    char *tok;
    char *word;

    uint32_t scope_count;

    struct _dataobject *objs;
    // To do: add line count, column number and more...
} intp_info;

//----------Lexer-------------
int _lex(intp_info *info);

//----------Parser------------
void _parse(intp_info *info);

//----------Data Types--------
void*intp_get_data(intp_info *info, char *name);
void intp_set_data(intp_info *info, const char* name, void *value, bool is_constant);

//----------Main--------------
int intp_init(intp_info *info);
int intp_free(intp_info *info);

void intp_string(intp_info *info , char *str);
void intp_file(intp_info *info, char *fn);

#endif
