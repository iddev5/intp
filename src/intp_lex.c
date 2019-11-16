#include "intp.h"

//////////////////////////////
//----------Lexer-------------
//////////////////////////////

#define OPR_COUNT 6

char *_operators[OPR_COUNT] = {
    "+", "-", "*", "/", "++", "--"
};

void _inc(int *n) {
    n++;
}

void _next(intp_info *info) {
    *info->data++;
}

void _send(intp_info *info, int n) {
    strcpy(info->word, info->tok);
    for(short i = 0; i < n; i++) {
        info->tok[i] = '\0';
    }
}


int _lex_opr(intp_info *info) {

    int times = 0;
    int type = -1;

    do {
        *(info->tok+times) = *info->data;
        _next(info);
        _inc(&times);

    } while(intp_is_sym(*info->data));


    if(strcmp(info->tok, "+")==0) type = op_add;
    else if(strcmp(info->tok, "-")==0) type = op_sub;
    else if(strcmp(info->tok, "++")==0) type = op_inc;
    else if(strcmp(info->tok, "--")==0) type = op_dec;

   /* for(int i = 0; i < OPR_COUNT; i++) {
        if(strcmp(info->tok, _operators[i])==0) type = op_add + i;
    }*/
    _send(info, times);

    return type;

}

int _lex_num(intp_info *info) {

    int times = 0;

    if(*info->data == '0') {
        *(info->tok+times) = *info->data;
        _next(info);
        _inc(&times);

        if(*info->data == 'x' || *info->data == 'X') {
            //*(info->tok+times) = *info->data;
            //goto add_numbers;
        }

        else if(*info->data == 'b' || *info->data == 'B') {
            //*(info->tok+times) = *info->data;
            //*info->data++; times++;
        }
    }
add_numbers:
    do {
        *(info->tok+times) = *info->data;

        _next(info);
        _inc(&times);

    } while(intp_is_num(*info->data));

    _send(info, times);

    return num;
}

int _lex_al(intp_info *info) {
   int times = 0;

   do {

        *(info->tok+times) = *info->data;

        _next(info);
        _inc(&times);

    } while(intp_is_id(*info->data));

    _send(info, times);

    return alpha;
}

int _lex(intp_info *info) {

    int type = -1;

    if(intp_is_space(*info->data)) {
        do { *info->data++; } while(intp_is_space(*info->data));
    }

    if(intp_is_sym(*info->data)) {
        type = _lex_opr(info);
    }

    if(intp_is_num(*info->data)) {
        type = _lex_num(info);
    }

    if(intp_is_id(*info->data)) {
        type = _lex_al(info);
    }

    return type;
}

/////////////////////////////////
/////////TEMP////////////////////
/////////////////////////////////
/*

char *_lex_operators[12] = {
    "+", "-", "*", "/", "^", "%",
    "=", "==","<", ">", "<=",">="
};
*/
/*
int _lex_check_exe_sym(intp_info *info) {
    for(int i = 0; *(_lex_symbols+i) != '\0'; i++) {
        if(*info->data == *(_lex_symbols+i)) {
            *info->tok = *info->data;
            strcpy(info->word, info->tok);
            *info->data++;
            *info->tok = '\0';
            return sym;
        }
    }
}



*/    //int times = 0;
/*
    for(int i = 0; i < 28; i++) {
        if(*info->data == *(_lex_symbols+i)) {
            *(info->tok+times) = *info->data;
            *info->data++; times++;
            printf("data: %c\tsym: %c\ttok: %s\n",
                   *info->data, _lex_symbols[i], info->tok);
        }
    }
*/
/*
    for(int i = 0; i < 12; i++) {
        if(strcmp(info->tok, _lex_operators[i])) {
            strcpy(info->word, info->tok);
            for(int i = 0; i < times; i++) *(info->tok+times) = '\0';
            return sym;
        }
    }
*/

/*
        if(*info->data == '+') {

            _next(info); times++;

            if(*info->data == '+') {
                printf("first tok: %s\t", info->tok);
                type = op_inc;
                break;

            }
            else {
                printf("first tok: %s\t", info->tok);
                type = op_add;
                break;

            }
        }

        else if(*info->data == '-') {

            _next(info); times++;

            if(*info->data == '-') {
                printf("first tok: %s\t", info->tok);
                type = op_dec;
                break;

            }
            else {
                printf("first tok: %s", info->tok);
                type = op_sub;
                break;

            }
        }*/
