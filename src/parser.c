#include "intp.h"

// Not sure whether to use throughout rest of the source code.
#include "sds/sds.h"

//////////////////////////////
//----------Parser------------
//////////////////////////////

#define INTP_DEBUG 

void _parse(intp_info *info) {

    int lex_info = -1;
	
	intp_set_data(info, "nl", "\n", false);
	intp_set_data(info, "tab","\t", false);

    while(1) {

        /* For Test */
        #ifdef INTP_DEBUG
        printf("token: %s\t\ttype:%d\n", info->tok, lex_info);
        #endif

        if(strcmp(info->tok, "var")==0) {
            // Get the variable name.
            lex_info = _lex(info);
            sds var_name = sdsnew(info->tok);

            lex_info = _lex(info);

            if(strcmp(info->tok, "=")==0) {
                
                sds var_value = sdsempty();
                
				int n = 0;
                do {
                    lex_info = _lex(info);
					
                    if(!strcmp(info->tok, ";")) break;
					else if(n != 0) strcat(var_value, " ");
					
                    strcat(var_value, info->tok);
					
					n++;
                } while(1);
      
                intp_set_data(info, sdsnew(var_name), sdsnew(var_value), false);

                sdsfree(var_value);
            }
            sdsfree(var_name);

        }

        if(strcmp(info->tok, "put")==0) {
            do {	
				lex_info = _lex(info);
				
				printf("%s", (char*)(intp_get_data(info, info->tok)));
					
				lex_info = _lex(info);
				
				if(!strcmp(info->tok, ";")) break;
				else if(!strcmp(info->tok, ",")) continue;
				
			} while(1);
        }

        if(*info->data == '\0') break;
        lex_info = _lex(info);

    }

}
