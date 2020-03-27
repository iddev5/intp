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
                    switch(type) {
                        case PLUSEQU: { 
                            if(data->type == val->type) {
                                if(data->type == STR_T) { strcat(data->val.str, val->val.str); }
                                else if(data->type == NUM_T) { data->val.num += val->val.num; }
                                else { intp_error(buf, "Operands are of unknown type"); }
                            }
                            else { intp_error(buf, "Operands are of different type"); } 
                            break; 
                        }
                        case MINEQU: { 
                            if(data->type == val->type) {
                                if(data->type == NUM_T) { data->val.num -= val->val.num; }
                                else { intp_error(buf, "Operands are of unknown type"); }
                            }
                            else { intp_error(buf, "Operands are of different type"); } 
                            break; 
                        }
                        case MULEQU: { 
                            if(data->type == val->type) {
                                if(data->type == NUM_T) { data->val.num *= val->val.num; }
                                else { intp_error(buf, "Operands are of unknown type"); }
                            }
                            else { intp_error(buf, "Operands are of different type"); } 
                            break; 
                        }
                        case DIVEQU: { 
                            if(data->type == val->type) {
                                if(data->type == NUM_T) { data->val.num /= val->val.num; }
                                else { intp_error(buf, "Operands are of unknown type"); }
                            }
                            else { intp_error(buf, "Operands are of different type"); } 
                            break; 
                        }
                        case MODEQU: { 
                            if(data->type == val->type) {
                                if(data->type == NUM_T) { data->val.num = (int64_t)data->val.num % (int64_t)val->val.num; }
                                else { intp_error(buf, "Operands are of unknown type"); }
                            }
                            else { intp_error(buf, "Operands are of different type"); } 
                            break; 
                        }
                        case POWEQU:
                        case FLOOREQU:
                        case XOREQU: 
                        case BNOTEQU:
                        case BANDEQU:
                        case BOREQU: 
                        case LSHEQU: 
                        case RSHEQU: break;
                    }
                }
                check_semi(buf, info);
            
            }

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
            case NUM_T : { printf("%s = %Lf\n", var->name, var->val.num);  break; }
            case STR_T : { printf("%s = %s\n" , var->name, var->val.str);  break; }
        }
        
    }
#endif
}