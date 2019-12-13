#include "intp.h"

// Not sure whether to use throughout rest of the source code.
#include "sds/sds.h"

//////////////////////////////
//----------Parser------------
//////////////////////////////

//#define INTP_DEBUG 

#define match(x) (strcmp(info->buf->tok, x)==0)

#define lex()   _lex(info->buf);

void *eval(intp_info *info) {
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

    return -1;
}

void _var_stmt(intp_info *info) {
    // Get the variable name.
    int i = lex();
    sds var_name = sdsnew(info->buf->tok);

    i = lex();

    if(strcmp(info->buf->tok, "=")==0){
        void *x = eval(info);
        intp_set_data(info, sdsnew(var_name), sdsnew(x), false);
    }
    sdsfree(var_name);
}

void _stmt(intp_info *info) {
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

void _parse(intp_info *info) {

    int token = -1;
	
	intp_set_data(info, "nl", "\n", false);
	intp_set_data(info, "tab","\t", false);

    while(1) {

        /* For Test */
        #ifdef INTP_DEBUG
            printf("token: %s\t\ttype:%d\n", info->buf->tok, token);
        #endif

        switch(token) {
            case kwd_var: _var_stmt(info); break;
            default:      _stmt(info); break;
        }
        
        if(*info->buf->data == '\0') break;
        token = lex();

    }

}
