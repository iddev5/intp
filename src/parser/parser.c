#include "../intp.h"

//////////////////////////////
//----------Parser------------
//////////////////////////////

//#define INTP_DEBUG

class var_stmt_ast {
    char *name;
    void *value;
} var_stmt_ast;

void intp_parse(intp_info *info) {
    while(1) {

        /* For Test */
        #ifdef INTP_DEBUG
            printf("token: %s\t\ttype:%d\n", info->buf->tok, info->buf->type);
        #endif

        switch(info->buf->type) {
            case kwd_var:
                intp_lex(info->buf); // Get the identifier name
                if(info->buf->type != ident) {
                    intp_error(info->buf, "Reserved words are not allowed as identifiers.");
                }
                else {
                    printf("Found variable: %s\n", info->buf->tok);
                }
            break;
        }
        
        if(*info->buf->data == '\0') break;
        intp_lex(info->buf);

    }

}
