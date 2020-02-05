#include "intp.h"

//////////////////////////////
//----------Parser------------
//////////////////////////////

#define INTP_DEBUG 

#define match(x) (strcmp(info->buf->tok, x)==0)

#define lex()   intp_lex(info->buf);

void *intp_eval(intp_info *info) {
    int i;
    i = lex();

    if(i == string) {
            
        sds ret = sdsnew(info->buf->tok);

        i = lex();
        switch(i) {
            case op_add: 
                i = lex();
                switch(i) {
                    case string: 
                        ret = sdscat(ret, info->buf->tok);
                    break;
                    case semicol:
                        intp_error(info->buf, "Expected a string before \';\'");
                    break;
                }
            break;
                
            case op_sub: 
                intp_error(info->buf, "Not implemented yet");
            break;
        }
        return ret;
    }

        else if (i == semicol) {
            intp_error(info->buf, "Expected an expression before \';\'");
        }

    return (int*)-1;
}

void var_stmt(intp_info *info) {
    // Get the variable name.
    lex();
    sds var_name = sdsnew(info->buf->tok);

    lex();

    if(strcmp(info->buf->tok, "=")==0){
        void *x = intp_eval(info);
        intp_set_data(info, sdsnew(var_name), sdsnew(x), false);
    }
    sdsfree(var_name);
}

void stmt(intp_info *info) {
    if(match("put")) {
        do {	
			lex();
				
			printf("%s", (char*)(intp_get_data(info, info->buf->tok)));
					
			lex();
				
			if(match(";")) break;
			else if(match(",")) continue;
				
		} while(1);
    }

}

void intp_parse(intp_info *info) {

    int token = -1;

    while(1) {

        /* For Test */
        #ifdef INTP_DEBUG
            printf("token: %s\t\ttype:%d\n", info->buf->tok, token);
        #endif
        
        if(*info->buf->data == '\0') break;
        token = lex();

    }

}
