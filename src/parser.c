#include "intp.h"

//////////////////////////////
//----------Parser------------
//////////////////////////////

#define INTP_DEBUG 

void intp_parse(intp_info *info) {
    while(1) {

        /* For Test */
        #ifdef INTP_DEBUG
            printf("token: %s\t\ttype:%d\n", info->buf->tok, token);
        #endif
        
        if(*info->buf->data == '\0') break;
        intp_lex(info->buf);

    }

}
