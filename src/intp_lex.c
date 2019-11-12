#include "intp.h"

//////////////////////////////
//----------Lexer-------------
//////////////////////////////

void intp__lex_next_ch(intp_info *info) {
    *info->data++;
}


int intp__lex_opr(intp_info *info) {

    //strcpy(info->word, "");

    int times = 0;
    int type = -1;

    do {
        *(info->tok+times) = *info->data;

        if(*info->data == '+') {

            intp__lex_next_ch(info); times++;

            if(*info->data == '+') {
                type = op_inc;
                //strcpy(info->word, "++");
                //intp__lex_next_ch(info);
                //return op_inc;
            }
            else {
                type = op_add;
                //strcpy(info->word, "+");
                //intp__lex_next_ch(info);
                //return op_add;
            }
        }

        else if(*info->data == '-') {

            intp__lex_next_ch(info); times++;

            if(*info->data == '-') {
                type = op_dec;
                //strcpy(info->word, "--");
                //intp__lex_next_ch(info);
                //return op_dec;
            }
            else {
                type = op_sub;
                //strcpy(info->word, "-");
                //intp__lex_next_ch(info);
                //return op_sub;
            }
        }

    } while(intp_is_sym(*info->data));

    strcpy(info->word, info->tok);

    for(int i = 0; i <= times; i++) *(info->tok+i) = '\0';

    printf("just before: %d\n", type);

    return type;

}

int intp__lex_num(intp_info *info) {

    int times = 0;

    if(*info->data == '0') {
        *(info->tok+times) = *info->data;
        *info->data++; times++;

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

        printf("num: %s", info->tok);
        printf("\tdata: %c", *info->data);

        *info->data++;
        times++;

        printf("\ttimes: %d\n", times);

    } while(intp_is_num(*info->data));

    strcpy(info->word, info->tok);

    for(int i = 0; i <= times; i++) *(info->tok+i) = '\0';

    return num;
}

int intp__lex_al(intp_info *info) {
   int times = 0;

   do {

        *(info->tok+times) = *info->data;

        printf("id: %s\t", info->tok);
        printf("data: %c\n", *info->data);

        *info->data++;
        times++;

    } while(intp_is_id(*info->data));

    strcpy(info->word, info->tok);

    for(int i = 0; i <= times; i++) *(info->tok+i) = '\0';

    return alpha;
}

int intp__lex(intp_info *info) {

    int type = -1;

    if(intp_is_space(*info->data)) {
        do { *info->data++; } while(intp_is_space(*info->data));
    }

    type = intp__lex_opr(info);

    if(intp_is_num(*info->data)) {
        type = intp__lex_num(info);
    }

    if(intp_is_id(*info->data)) {
        type = intp__lex_al(info);
    }

    return type;
}

/////////////////////////////////
/////////TEMP////////////////////
/////////////////////////////////
/*

char *intp__lex_operators[12] = {
    "+", "-", "*", "/", "^", "%",
    "=", "==","<", ">", "<=",">="
};
*/
/*
int intp__lex_check_exe_sym(intp_info *info) {
    for(int i = 0; *(intp__lex_symbols+i) != '\0'; i++) {
        if(*info->data == *(intp__lex_symbols+i)) {
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
        if(*info->data == *(intp__lex_symbols+i)) {
            *(info->tok+times) = *info->data;
            *info->data++; times++;
            printf("data: %c\tsym: %c\ttok: %s\n",
                   *info->data, intp__lex_symbols[i], info->tok);
        }
    }
*/
/*
    for(int i = 0; i < 12; i++) {
        if(strcmp(info->tok, intp__lex_operators[i])) {
            strcpy(info->word, info->tok);
            for(int i = 0; i < times; i++) *(info->tok+times) = '\0';
            return sym;
        }
    }
*/
