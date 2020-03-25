#include "../intp.h"
#include "expr.h"

int get_binop_prec(intp_src_buf *buf) {
    int prec = -1;
    switch(buf->type) {
        case PLUS : prec = 10; break;
        case MINUS: prec = 20; break;
        case MULTI: prec = 30; break;
        case DIV  : prec = 40; break;  
    }

    return prec;
}

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

intp_data *rhs_expr(int expr_prec, intp_data *lhs, intp_src_buf *buf, intp_info *info) {
    int64_t val;

    while(true) {
        int tok_prec = get_binop_prec(buf);
        if(tok_prec < expr_prec) {
            return lhs;
        }

        /* Get the operator */
        int bin_op = buf->type;
        intp_lex(buf);

        intp_data *rhs = atom(buf, info);

        int next_prec = get_binop_prec(buf);
        if(tok_prec < next_prec) {
            rhs = rhs_expr(tok_prec+1, rhs, buf, info);
        }

        /* Compute the values */
        real_t val0, val1;

        val0 = (lhs->type == NUM_T) ? (real_t)lhs->val.num : lhs->val.real;
        val1 = (rhs->type == NUM_T) ? (real_t)rhs->val.num : rhs->val.real;

        switch(bin_op) {
            case PLUS : val = val0 + val1; break;
            case MINUS: val = val0 - val1; break;
            case MULTI: val = val0 * val1; break;
            case DIV  : 
                if(rhs->val.num != 0) { val = val0 / val1; }
                else { intp_error(buf, "Division by zero"); } 
                break;
        }
        lhs = NEW_DATA("", NUM_T, &val);
    }
}

/* sum ::= atom [+|- atom] ... */
intp_data *sum(intp_src_buf *buf, intp_info *info) {
    intp_data *x, *to_return;
    x = atom(buf, info);

    switch(x->type) {
        case NUM_T: case REAL_T: to_return = rhs_expr(0, x, buf, info); break;
        case STR_T: to_return = x; /* For now, string can't do anything */
    }

    return to_return;
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