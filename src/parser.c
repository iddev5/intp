#include "intp.h"

// Not sure whether to use throughout rest of the source code.
#include "sds/sds.h"

//////////////////////////////
//----------Parser------------
//////////////////////////////

//#define INTP_DEBUG 

#define match(x) (strcmp(info->tok, x)==0)

#define lex()   _lex(info);

void *eval(intp_info *info) {
    int i;
    i = lex();

    if(i == string) {
            
        sds ret = sdsnew(info->tok);

        i = lex();
        switch(i) {
            case op_add: 
                i = lex();
                switch(i) {
                    case string: 
                        ret = sdscat(ret, info->tok);
                    break;
                    case semicol:
                        intp_error(info, "Expected a string before \';\'");
                    break;
                }
            break;
                
            case op_sub: 
                intp_error(info, "Not implemented yet");
            break;
        }
        return ret;
    }

        else if (i == semicol) {
            intp_error(info, "Expected an expression before \';\'");
        }

    return -1;
}

void _var_stmt(intp_info *info) {
    // Get the variable name.
    int i = lex();
    sds var_name = sdsnew(info->tok);

    i = lex();

    if(strcmp(info->tok, "=")==0){

        void *x = eval(info);
        intp_set_data(info, sdsnew(var_name), sdsnew(x), false);

        sdsfree(var_value);
    }
    sdsfree(var_name);
}

void _stmt(intp_info *info) {
    if(match("put")) {
        do {	
			lex();
				
			printf("%s", (char*)(intp_get_data(info, info->tok)));
					
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
            printf("token: %s\t\ttype:%d\n", info->tok, token);
        #endif

        switch(token) {
            case kwd_var: _var_stmt(info); break;
            default:      _stmt(info); break;
        }
        
        if(*info->data == '\0') break;
        token = lex();

    }

}
