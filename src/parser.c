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
    int type = -1;
    intp_data *x, *y;

    x = atom(info);
    type = info->buf->type; intp_lex(info->buf);
    y = atom(info); 

    while((type == PLUS || type == MINUS)) {

        printf("before_1: %ld\n", x->val.inn); 
        printf("before_2: %ld\n", y->val.inn);

        int64_t i = (type == PLUS) ? (x->val.inn + y->val.inn) : (x->val.inn - y->val.inn);
        x = new_data("", INT, &i); 
        
        type = info->buf->type;
        intp_lex(info->buf);

        y = atom(info); 
        printf("after0: %ld\n", x->val.inn);
    }
    
    intp_lex(info->buf);
    return x;
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


        if(*info->buf->data == '\0') break;
    }
        printf("To return: %ld\n", to_return->val.inn);

    return to_return;
}