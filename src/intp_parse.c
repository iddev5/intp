#include "intp.h"

//////////////////////////////
//----------Parser------------
//////////////////////////////

void intp__parse(intp_info *info) {

    //intp__lex(info);
    int lex_info = -1;

    while(1) {

        /*<---------------------->*/
        printf("word: %s\t\ttype:%d\n", info->word, lex_info);
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
        lex_info = intp__lex(info);

    }

}
