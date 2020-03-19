#include "intp.h"

void intp_parse(intp_info* info) {
    int i = 0;
    while(true) {
        switch(i) {
            case NUM: printf("NUM = %d\n", info->buf->val.inn); break;
            case IDENTIFIER: printf("IDENT = %s\n", info->buf->tok); break;
            default: printf("%d\n", i); break;
        }

        if(*info->buf->data == '\0') break;
        i = intp_lex(info->buf);
    }
}