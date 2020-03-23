#include "../intp.h"

void stmt(intp_src_buf *buf, intp_info *info) {
    switch(buf->type) {
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
            }
            
            if(buf->type != SEMI) { 
                intp_error(buf, "Expected ; at the end of statement-expression"); 
            }
            else { intp_lex(buf); }

            break;
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
    for(int i = 0; i < arrlen(info->objs); i++) {
        printf("%s = %ld\n", info->objs[i]->name, info->objs[i]->val.inn);
    }
#endif
}