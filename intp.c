#include "intp.h"

//////////////////////////////
//----------Logging-----------
//////////////////////////////

void intp__warn(char *str) {
    printf("%s\n", str);
}

int intp__error(char *str) {
    printf("%s\n", str);
    return -1;
}

//////////////////////////////
//----------Lexer-------------
//////////////////////////////

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

int intp__lex_next_ch(intp_info *info) {
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

        printf("id: %s", info->tok);
        printf("\tdata: %c", *info->data);

        *info->data++;
        times++;

        printf("\ttimes: %d\n", times);

    } while(intp_is_id(*info->data));

    strcpy(info->word, info->tok);

    for(int i = 0; i <= times; i++) *(info->tok+i) = '\0';

    return al;
}

int intp__lex(intp_info *info) {

    if(intp_is_space(*info->data)) {
        do { *info->data++; } while(intp_is_space(*info->data));
    }

    intp__lex_opr(info);

    if(intp_is_num(*info->data)) {
        return intp__lex_num(info);
    }

    if(intp_is_id(*info->data)) {
        return intp__lex_al(info);
    }
}

//////////////////////////////
//----------Parser------------
//////////////////////////////

void intp__parse(intp_info *info) {

    //intp__lex(info);

    while(1) {

        /*<---------------------->*/
        printf("word: %s\n", info->word);
        if(strcmp(info->word, "hi") == 0) {
            printf("output: \"this is a hi\"\n");
        }

        if(strcmp(info->word, "hello") == 0) {
            printf("output: \"this is a hello\"\n");
        }

        if(strcmp(info->word, "notsup") == 0) {
            printf("output: \"this is not a sup\"\n");
        }

        if(strcmp(info->word, "sup") == 0) {
            printf("output: \"but this is indeed a sup\"\n");
        }

        if(*info->data == '\0') break;
        intp__lex(info);

    }

}

//////////////////////////////
//----------Main--------------
//////////////////////////////

int intp_init(intp_info *info) {

    info->tok  = (char*)malloc(sizeof(char)*32);
    info->word = (char*)malloc(sizeof(char)*32);

    //*result |= (info->tok && info->word) ? 1 : 0;

    return (info->tok && info->word) ? 1 : 0;
}

int intp_free(intp_info *info) {
    free(info->data);
    free(info->tok );
    free(info->word);
}

void intp_string(intp_info *info , char *str) {
    info->data = (char*)malloc(sizeof(char) * (strlen(str)+1));
    if(!info->data) {
        intp__error("Cannot allocate memory.");
    }

    size_t r = (size_t)strcpy(info->data, str);
    if(!r) {
        intp__error("Cannot read string.");
    }

    intp__parse(info);
}

void intp_file(intp_info *info, char *fn) {

    FILE *file = fopen(fn, "r");

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    printf("file size: %ld\n", size);

    info->data = (char*)malloc(sizeof(char) * size);

    if(!info->data) {
        intp__error("Cannot allocate memory.");
    }

    size_t r = fread(info->data, 1, size+1, file);
    if(!r) {
        intp__error("Cannot read file.");
    }

    fclose(file);
    strcat(info->data, "\0");
    intp__parse(info);
}
