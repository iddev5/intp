#include "intp.h"

/* Forward declaration */
intp_data *expr(intp_info *info);
intp_data *paren_expr(intp_info *info);

intp_data *atom(intp_info *info) {
    intp_data *to_return;
    switch(info->buf->type) {
        case NUM: to_return = new_data("", INT, &info->buf->val.inn); break;
        case IDENTIFIER: to_return = intp_get_data(info, info->buf->tok); break;
        case STRING: to_return = new_data("", STR, info->buf->tok); break;
        default: to_return = paren_expr(info); break;
    }
    intp_lex(info->buf);
    return to_return;
}

intp_data *sum(intp_info *info) {
    int type = -1;
    intp_data *x, *y;

    x = atom(info);
    type = info->buf->type;

    while((type == PLUS || type == MINUS)) {
        intp_lex(info->buf);
        y = atom(info);

        int64_t i = (type == PLUS) ? (x->val.inn + y->val.inn) : (x->val.inn - y->val.inn);
        x = new_data("", INT, &i); 
        
        type = info->buf->type;
    }
    
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
    else { to_return = sum(info); }
    intp_lex(info->buf);
    return to_return;
}

intp_data *intp_parse(intp_info* info) {
    intp_data *to_return;

    intp_lex(info->buf);
    while(true) {
        to_return = expr(info); 
        printf("To return: %d\n", (int)to_return->val.inn);

        //printf("it is %d\n", info->buf->type);
        //if(info->buf->type != SEMI) printf("Expected ; at the end of statement-expression.\n");
        if(*info->buf->data == '\0') break;
    }

    return to_return;
}