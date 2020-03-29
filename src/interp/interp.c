#include "../intp.h"
#include "expr.h"

void check_semi(intp_src_buf *buf, intp_info *info) {
    if(buf->type != SEMI) {
#ifdef INTP_DEBUG
        printf("Token Found: %d\n", buf->type); 
#endif
        intp_error(buf, "Expected ; at the end of statement-expression"); 
    }
    else { intp_lex(buf); }
}

void stmt(intp_src_buf *buf, intp_info *info) {
    switch(buf->type) {
        case KWD_IF: {
            bool passed = false;
            intp_data *cond;
_else_if:   
            intp_lex(buf);
            cond = expr(buf, info); /* Condition of the If-statement */
            if(cond->val.num > 0) {
_else:
                /* The statment can be a single statement or 
                 * a group of statements enclosed within { }
                 */
                stmt(buf, info);
                /* Now, we don't need to parse else if or else */
                passed = true;
            }
            else {
_skip:
                /* If it is LBRAC then skip till RBRAC else skip till SEMI */
                if(buf->type == LBRAC) { 
                       do { intp_lex(buf); } while(buf->type != RBRAC); intp_lex(buf); }
                else { do { intp_lex(buf); } while(buf->type != SEMI);  intp_lex(buf); }
            }

            if(buf->type == KWD_ELSE) {
                intp_lex(buf);
                /* 'else if' */
                if(buf->type == KWD_IF) { 
                    if(passed) {
                        /* First consume the conditional expr and then consume the rest using _skip */
                        while(buf->type != LBRAC) { intp_lex(buf); } 
                        goto _skip; 
                    } 
                    else { goto _else_if; } }
                /* 'else' */
                else { 
                    if(passed) { goto _skip; } 
                    else       { goto _else; } 
                }
            }

            break; 
        }

        /* Variable declaration, function declaration, function call */
        case IDENTIFIER: {
            intp_data *val;
            char *name = NEW_STRING(buf->tok);
            
            int type = intp_lex(buf);

            /* Variable assignment */
            if(type >= EQU && type <= RSHEQU) {
                intp_lex(buf); /* Eat = */
                val = expr(buf, info);
                val->name = name;

                if(type == EQU) {
                    intp_set_data_from(info, val);
                } 
                else {
                    intp_data *data = intp_get_data(info, val->name);
                    
                    /* WIP Section */
                    if(data->type == val->type) {
                        if(data->type == STR_T) {
                            if(type == PLUSEQU) { strcat(data->val.str, val->val.str); }
                            else { intp_error(buf, "Invalid operation for string"); }
                        }
                        else if(data->type == NUM_T) {
                            switch(type) {
                                case PLUSEQU: data->val.num += val->val.num; break;
                                case MINEQU : data->val.num -= val->val.num; break;
                                case MULEQU : data->val.num *= val->val.num; break;
                                case DIVEQU : case FLOOREQU:
                                    if(val->val.num != 0) { data->val.num /= val->val.num; }
                                    if(type == FLOOREQU) { data->val.num = FLOORf(data->val.num); }
                                    else { intp_error(buf, "Division by zero"); } break;
                                case POWEQU: data->val.num = POWf(data->val.num, val->val.num); break;
                                case MODEQU: 
                                    if(val != 0) { data->val.num = (int64_t)data->val.num % (int64_t)val->val.num; }
                                    else { intp_error(buf, "Division by zero"); } break;
                                    break;
                                case XOREQU: 
                                case BNOTEQU:
                                case BANDEQU:
                                case BOREQU: 
                                case LSHEQU: 
                                case RSHEQU: break;
                            }
                        }
                    }
                    else { intp_error(buf, "Operands are of different type"); }
                }
                check_semi(buf, info);
            break;
            }
        }
        case LBRAC: {
            info->scope++;
            intp_lex(buf);

            while(true) {
                if(buf->type == RBRAC) {  
                    long i = 0;
                    while(i < (stbds_arrlen(info->objs))) {
                        intp_data *data = info->objs[i];
                        if(info->scope == data->scope) { stbds_arrdel(info->objs, i); i--; } 
                        else { i++; }
                    }
                    info->scope--;
                    intp_lex(buf);
                    break;
                }
                else { stmt(buf, info); }
            }

            break;
        }
        case RBRAC: {
            intp_error(buf, "Unexpected RBRAC }");
            break;
        }
#ifdef INTP_DEBUG
        case TMP_PUTS: {
            intp_data *val;

            while(true) {
                intp_lex(buf);
                val = expr(buf, info);
                
                switch(val->type) {
                    case NUM_T : { printf("%Lf", val->val.num); break; }
                    case STR_T : {
                        if(!strcmp(val->val.str, "\\n")) { printf("\n"); }
                        else if(!strcmp(val->val.str, "\\t")) { printf("\t"); }
                        else { printf("%s",  val->val.str); }
                        break;
                    }
                }

                if(buf->type != COMMA) { break; }
            };

            check_semi(buf, info);
        }
#endif
    }
}

void intp_interp(intp_src_buf *buf, intp_info* info) {
    intp_lex(buf);
    while(true) {
        stmt(buf, info);
        
        if(*buf->data == '\0') { break; }
    }

#ifdef INTP_DEBUG
    printf("===============VARIABLES===============\n");
    for(int i = 0; i < stbds_arrlen(info->objs); i++) {
        intp_data *var = info->objs[i];
        switch(var->type) {
            case NUM_T : { printf("%s = %Lf    scope = %u\n", var->name, var->val.num, var->scope);  break; }
            case STR_T : { printf("%s = %s     scope = %u\n", var->name, var->val.str, var->scope);  break; }
        }
        
    }
#endif
}