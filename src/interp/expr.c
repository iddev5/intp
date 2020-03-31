#include "../intp.h"
#include "expr.h"

int get_binop_prec(intp_src_buf *buf) {
    int prec = -1;
    switch(buf->type) {
        /* Subject to change */
        case WAL: prec = 3; break;
        case KWD_OR:   prec = 4; break;
        case KWD_AND:  prec = 5; break;
        case BOR:  prec = 6; break;
        case XOR:  prec = 7; break;
        case BAND: prec = 8; break;
        case COMP: case NOTEQU: prec = 9; break;
        case GRT:  case GRTEQU: 
        case LES:  case LESEQU: prec = 10; break;
        case LSHIFT: case RSHIFT: prec = 11; break; 
        case PLUS :  case MINUS:  prec = 12; break;
        case MULTI:  case DIV: 
        case FLOOR:  case MOD: prec = 13; break;
        case POW: prec = 14; break;
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

intp_data *unop_expr(intp_src_buf *buf, intp_info *info) {
    int type = buf->type;
    intp_data *to_return;

    if(type == PLUS || type == MINUS || type == NOT) {
        intp_data *data;

        intp_lex(buf);
        data = atom(buf, info);

        if(data->type == NUM_T) {
            switch(type) {
                case MINUS: case NOT: {
                    real_t val = -(data->val.num);
                    to_return = NEW_DATA("", NUM_T, &val);
                    break;
                }
                /* Includes PLUS i.e do nothing */
                default: { to_return = data; break; }
            }
        }
        else { intp_error(buf, "Prefix unary operators are not supported with string"); }
        free(data);
    }
    else {
        to_return = atom(buf, info);
    }

    return to_return;
}

intp_data *binop_expr(int expr_prec, intp_data *lhs, intp_src_buf *buf, intp_info *info) {
    real_t val = 0;
    intp_data *rhs;

    while(true) {
        int tok_prec = get_binop_prec(buf);
        if(tok_prec < expr_prec) {
            return lhs;
        }

        /* Get the operator */
        int bin_op = buf->type;
        intp_lex(buf);

        rhs = atom(buf, info);

        int next_prec = get_binop_prec(buf);
        if(tok_prec < next_prec) {
            rhs = binop_expr(tok_prec+1, rhs, buf, info);
        }

        /* Compute the values */
        real_t val0, val1;

        val0 = lhs->val.num;
        val1 = rhs->val.num;

        switch(bin_op) {
            case PLUS : val = val0 + val1; break;
            case MINUS: val = val0 - val1; break;
            case MULTI: val = val0 * val1; break;
            case DIV: case FLOOR: {
                if(val1 != 0) { val = val0 / val1; }
                else { intp_error(buf, "Division by zero"); }
                if(bin_op == FLOOR) { val = FLOORf(val); } 
                break;
            }
            case MOD: {
                if(val1 != 0) { val = (int64_t)val0 % (int64_t)val1; }
                else { intp_error(buf, "Division by zero"); }
                break;
            }
            case POW : val = POWf(val0, val1); break;  
            case GRT : val = val0 > val1;  break;
            case LES : val = val0 < val1;  break;
            case COMP: val = val0 == val1; break;
            case GRTEQU: val = val0 >= val1; break;
            case LESEQU: val = val0 <= val1; break; 
            case KWD_AND: val = val0 && val1; break;
            case KWD_OR : val = val0 || val1; break;
            case WAL: {
                intp_data *data = ALLOC(intp_data*, 1);
                data->name = NEW_STRING(lhs->name);
                data->type = rhs->type;
                data->val.num = val1;
                intp_set_data_from(info, data);
                val = val1; 
                break;
            }
            default: intp_error(buf, "Invalid operator"); break;
        }
        lhs = NEW_DATA("", NUM_T, &val);
    }
    free(rhs);
}

/* sum ::= atom [+|- atom] ... */
intp_data *operation(intp_src_buf *buf, intp_info *info) {
    intp_data *x, *to_return;
    x = unop_expr(buf, info);
    
    switch(x->type) {
        case NUM_T: to_return = binop_expr(0, x, buf, info); break;
        case STR_T: {
            int type = buf->type;
            intp_data *y;

            while(type == PLUS) {
                intp_lex(buf); 
                y = atom(buf, info);
                if(y->type != STR_T) {
                    intp_error(buf,  "Expected string after + operator");
                }

                strcat(x->val.str, y->val.str);
                type = buf->type;
            }
            to_return = x;
        }
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
    return operation(buf, info);
}