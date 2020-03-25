#include "../intp.h"
#include "expr.h"

/* Atom - the structural valued unit */
/* atom ::= num | string | id | paren_expr */
intp_data *atom(intp_src_buf *buf, intp_info *info) {
    intp_data *to_return;
    switch(buf->type) {
        case NUM: {
            to_return = NEW_DATA("", NUM_T, &buf->num); 
            intp_lex(buf); break;
        }
        case REAL: {
            to_return = NEW_DATA("", REAL_T, &buf->real);
            intp_lex(buf); break;
        }
        case STRING: {
            to_return = NEW_DATA("", STR_T, buf->tok); 
            intp_lex(buf); break;
        }
        case IDENTIFIER: {
            to_return = intp_get_data(info, buf->tok); 
            intp_lex(buf); break;
        }
        default: { to_return = paren_expr(buf, info); break; }
    }
    return to_return;
}

/* sum ::= atom [+|- atom] ... */
intp_data *sum(intp_src_buf *buf, intp_info *info) {
    int type = -1;
    intp_data *x, *y;

    x = atom(buf, info); 
    type = buf->type;
    
    while((type == PLUS || type == MINUS)) {
        intp_lex(buf);
        y = atom(buf, info);

        int64_t i = (type == PLUS) ? (x->val.num + y->val.num) : (x->val.num - y->val.num);
        x = NEW_DATA("", NUM_T, &i); 
        
        type = buf->type;
    }

    return x;
}

/* paren_expr ::= ( expr )*/
intp_data *paren_expr(intp_src_buf *buf, intp_info *info) {
    intp_data *to_return;
    
    if(buf->type == LPAREN) { intp_lex(buf); }
    else { intp_error(buf, "Expected ) at the end of expression"); }
    
    to_return = expr(buf, info);
    
    if(buf->type == RPAREN) { intp_lex(buf); }
    else { intp_error(buf, "Expected ) at the end of expression"); }

    return to_return;
}

/* expr ::= id = sum | sum */
intp_data *expr(intp_src_buf *buf, intp_info *info) {
    intp_data *to_return;
    to_return = sum(buf, info);
    return to_return;
}