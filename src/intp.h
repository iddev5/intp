#ifndef INTP_H
#define INTP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#define STBDS_NO_SHORT_NAMES
#include "../depends/stb_ds.h"

#define INTP_DEBUG

/*
 * Types
 */
 
#ifdef INTP_SHORT_TYPES
    typedef int32_t num_t;
    typedef double  real_t;
#else
    typedef int64_t     num_t;
    typedef long double real_t;
#endif

/*
 *----------Enums------------
 */
enum token_type {
    /* Standard types */
    NUM, STRING, IDENTIFIER,
    

    /* Operators and Symbols */
    LBRAC, RBRAC, LPAREN, RPAREN, LSQR, RSQR,
    SEMI, COL, COMMA, QUES,
    
    /* Arithmetic operators */
    PLUS, MINUS, MULTI, DIV, MOD, POW, FLOOR, 
    
    /* Relational operators */
    GRT, GRTEQU, LES, LESEQU, COMP, NOTEQU, 
    
    /* Logical operators */
    NOT, AND, OR, 

    /* Bitwise operators */
    XOR, BNOT, BAND, BOR, LSHIFT, RSHIFT, 

    /* Unary operators */
    INC, DEC,   

    /* Assignment operators */
    EQU, PLUSEQU, MINEQU, MULEQU, DIVEQU, 
    MODEQU, POWEQU, FLOOREQU, XOREQU, BNOTEQU, 
    BANDEQU, BOREQU, LSHEQU, RSHEQU, 


    /* Keywords */
	KWD_AND, KWD_BREAK, KWD_CONTINUE, KWD_DO,
    KWD_ELSE, KWD_FALSE, KWD_FOR, KWD_IF,
    KWD_IN, KWD_IMPORT, KWD_OR, KWD_RETURN,
    KWD_TRUE, KWD_WHILE

#ifdef INTP_DEBUG
    ,
    /* Temporary commands/keywords/functions */
    TMP_PUTS
#endif
};

enum data_type {
    NUM_T, STR_T
};

/*
 *----------Structs-----------
 */

typedef struct intp_data {
    char *name;
    uint8_t  type;
    uint32_t scope;
    
    union {
        real_t num;
        char *str;
    } val;

} intp_data;

typedef struct intp_src_buf {
    char *filename;
	uint32_t line, col, len;

    char *data;
	int32_t type;

    char *tok;
    real_t num;
    
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
int  intp_error_std(char *str, ...);

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
