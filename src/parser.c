#include "intp.h"

/* Forward declaration */
intp_data *expr(intp_src_buf *buf, intp_info *info);
intp_data *paren_expr(intp_src_buf *buf, intp_info *info);

intp_data *atom(intp_src_buf *buf, intp_info *info) {
    intp_data *to_return;
    switch(buf->type) {
        case NUM: 
            to_return = new_data("", INT, &buf->val.inn); 
            intp_lex(buf); break;
        case IDENTIFIER: 
            to_return = intp_get_data(info, buf->tok); 
            intp_lex(buf); break;
        case STRING: 
            to_return = new_data("", STR, buf->tok); 
            intp_lex(buf); break;
        default: to_return = paren_expr(buf, info); break;
    }
    return to_return;
}

intp_data *sum(intp_src_buf *buf, intp_info *info) {
    int type = -1;
    intp_data *x, *y;

    x = atom(buf, info); 
    type = buf->type;

    while((type == PLUS || type == MINUS)) {
        intp_lex(buf);
        y = atom(buf, info);

        int64_t i = (type == PLUS) ? (x->val.inn + y->val.inn) : (x->val.inn - y->val.inn);
        x = new_data("", INT, &i); 
        
        type = buf->type;
    }

    return x;
}

intp_data *paren_expr(intp_src_buf *buf, intp_info *info) {
    intp_data *to_return;
    
    if(buf->type == LPAREN) intp_lex(buf);
    /* else error */
    to_return = expr(buf, info);
    if(buf->type == RPAREN) intp_lex(buf);
    /* else error */

    return to_return;
}

intp_data *expr(intp_src_buf *buf, intp_info *info) {
    intp_data *to_return;
    to_return = sum(buf, info);
    intp_lex(buf);
    return to_return;
}

intp_data *intp_parse(intp_src_buf *buf, intp_info* info) {
    intp_data *to_return;

    intp_lex(buf);
    while(true) {
        to_return = expr(buf, info); 
        printf("To return: %d\n", (int)to_return->val.inn);

        //printf("it is %d\n", info->buf->type);
        //if(info->buf->type != SEMI) printf("Expected ; at the end of statement-expression.\n");
        if(*buf->data == '\0') break;
    }

    return to_return;
}