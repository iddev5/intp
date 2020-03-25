#ifndef INTP_MAIN_H
#define INTP_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#define STBDS_NO_SHORT_NAMES
#include "../depends/stb_ds.h"

#define INTP_DEBUG

/*
 *----------Enums------------
 */
enum token_type {
    NUM, REAL, STRING, IDENTIFIER,
    
    LBRAC, RBRAC, LPAREN, RPAREN,
    SEMI, COL, COMMA,
    PLUS, MINUS, MULTI, DIV, MOD, POW, FLOOR,
    XOR, LSHIFT, RSHIFT, 
    INC, DEC, GRT, LES, EQU, 
    COMPARE, PLUSEQU, MINEQU, MULEQU, DIVEQU, 
    MODEQU, XOREQU, GRTEQU, LESEQU, 

	KWD_AND, KWD_BREAK, KWD_CONTINUE, KWD_DO,
    KWD_ELSE, KWD_FALSE, KWD_FOR, KWD_IF,
    KWD_IN, KWD_IMPORT, KWD_OR, KWD_RETURN,
    KWD_TRUE, KWD_WHILE,

    TMP_PUTS
};

enum data_type {
    NUM_T, REAL_T, STR_T
};

/*
 *----------Structs-----------
 */
typedef long double real_t;

typedef struct intp_data {
    char *name;
    uint8_t  type;
    uint32_t scope;
    
    union {
        int64_t num;
        long double real;
        char *str;
    } val;

} intp_data;

typedef struct intp_src_buf {
	uint32_t line, col;
    char *data;
	int32_t type;

    char *tok;
    int64_t num;
    long double real;
    
} intp_src_buf;

typedef struct intp_info {
    uint32_t scope;
	intp_src_buf *buf;
    intp_data **objs;

} intp_info;

/* Log file of the interpreter. */
extern FILE *logfile;

/*
 *----------Lexer-------------
 */
int intp_lex(intp_src_buf *buf);

/*
 *----------Parser------------
 */
void intp_interp(intp_src_buf *buf, intp_info *info);

/*
 *----------Logging-----------
 */
void intp_warn(intp_src_buf *buf, char *str);
int  intp_error(intp_src_buf *buf, char *str);
int  intp_error_std(char *str);

/*
 *----------Data Types--------
 */
intp_data *intp_get_data(intp_info *info, char *name);
void intp_set_data(intp_info *info, const char* name, int type, void *value);
void intp_set_data_from(intp_info *info, intp_data *data);

/*
 *----------Main--------------
 */
int  intp_init(intp_info *info);
void intp_free(intp_info *info);

void intp_string(intp_info *info , char *str);
void intp_file(intp_info *info, char *fn);

/*
 * Private Functions
 * It is not recomended to use these functions
 * for general purpose.
 */

#ifdef __c_plus_plus 
    #define ALLOC(type, size) (type)(malloc(sizeof(type)*(size))) 
#else
    #define ALLOC(type, size) malloc(sizeof(type)*(size))
#endif

char *NEW_STRING(const char *str);
intp_data *NEW_DATA(const char *name, int type, void *value);

#endif
