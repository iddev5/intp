#include "../intp.h"

void stmt(intp_src_buf *buf, intp_info *info) {
    switch(buf->type) {
        /* Variable declaration, function declaration, function call */
        case IDENTIFIER: {
            intp_data *val;
            char *name = NEW_STRING(buf->tok);
            
            intp_lex(buf);

            /* Variable assignment */
            if(buf->type == EQU) { 
                intp_lex(buf); /* Eat = */
                val = expr(buf, info);
                val->name = name;
                intp_set_data_from(info, val);
                
                if(buf->type != SEMI) {
                    printf("Found: %d\n", buf->type); 
                    intp_error(buf, "Expected ; at the end of statement-expression"); 
                }
                else { intp_lex(buf); }
            }

            break;
        }
        case TMP_PUTS: {
            intp_data *val;

            while(true) {
                intp_lex(buf);
                val = expr(buf, info);
                
                switch(val->type) {
                    case INT: printf("%ld", val->val.inn); break;
                    case STR: {
                        if(!strcmp(val->val.str, "\\n")) { printf("\n"); }
                        else if(!strcmp(val->val.str, "\\t")) { printf("\t"); }
                        else { printf("%s",  val->val.str); }
                        break;
                    }
                }

                if(buf->type != COMMA) break;
            };

            if(buf->type != SEMI) { 
                intp_error(buf, "Expected ; at the end of statement-expression"); 
            }
            else { intp_lex(buf); }
        }
    }
}

void intp_interp(intp_src_buf *buf, intp_info* info) {
    intp_lex(buf);
    while(true) {
        stmt(buf, info);
        
        if(*buf->data == '\0') break;
    }

#ifdef INTP_DEBUG
    printf("===============VARIABLES===============\n");
    for(int i = 0; i < arrlen(info->objs); i++) {
        intp_data *var = info->objs[i];
        switch(var->type) {
            case INT: printf("%s = %ld\n", var->name, var->val.inn); break;
            case STR: printf("%s = %s\n",  var->name, var->val.str); break;
        }
        
    }
#endif
}