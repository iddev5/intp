#include "intp.h"

/* Forward declaration */
intp_data *expr(intp_info *info);

intp_data *atom(intp_info *info) {
    intp_data *to_return;
    switch(info->buf->type) {
        case NUM: to_return = new_data("", INT, &info->buf->val.inn); break;
        case IDENTIFIER: to_return = intp_get_data(info, info->buf->tok); break;
        case STRING: to_return = new_data("", STR, info->buf->tok); break;
    }

    intp_lex(info->buf);
    return to_return;
}

intp_data *sum(intp_info *info) {
    intp_data *to_return, *x, *y = atom(info);

    if(info->buf->type == PLUS) {
        x = atom(info);
        if(x->type == y->type) {
            if(x->type == INT) {
                int64_t i = (x->val.inn + y->val.inn);
                to_return = new_data("", INT, &i);
            }
        }
    }
    
    intp_lex(info->buf);
    return to_return;
} 

intp_data *paren_expr(intp_info *info) {
    intp_data *to_return;
    
    if(info->buf->type == LPAREN) intp_lex(info->buf);
    /* else error */
    to_return = expr(info);
    if(info->buf->type == RPAREN) intp_lex(info->buf);
    /* else error */

    return to_return;
}

intp_data *expr(intp_info *info) {
    intp_data *to_return;
    if(info->buf->type == LPAREN) to_return = paren_expr(info);
    else to_return = sum(info);
    intp_lex(info->buf);
    return to_return;
}

intp_data *intp_parse(intp_info* info) {
    intp_data *to_return;

    intp_lex(info->buf);
    while(true) {
        switch(info->buf->type) {
            
            default: to_return = expr(info); break;
        }

        printf("To return: %ld\n", to_return->val.inn);

        if(*info->buf->data == '\0') break;
    }

    return to_return;
}