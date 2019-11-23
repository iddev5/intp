#include "intp.h"

// Not sure whether to use throughout rest of the source code.
#include "sds/sds.h"

//////////////////////////////
//----------Parser------------
//////////////////////////////

//#define INTP_DEBUG

void _parse(intp_info *info) {

    int lex_info = -1;


    while(1) {

        /* For Test */
        #ifdef INTP_DEBUG
        printf("token: %s\t\ttype:%d\n", info->word, lex_info);
        #endif

        if(strcmp(info->word, "var")==0) {
            // Get the variable name.
            lex_info = _lex(info);
            sds var_name = sdsnew(info->word);

            lex_info = _lex(info);

            if(strcmp(info->word, "=")==0) {
                /*
                while(strcmp(info->word, ";")!=0) {
                    lex_info = _lex(info);
                }
                */
                // Get the variable value.
                lex_info = _lex(info);
                sds var_value = sdsnew(info->word);

                intp_set_data(info, sdsnew(var_name), sdsnew(var_value), false);

                sdsfree(var_value);
            }
            sdsfree(var_name);

        }

        if(strcmp(info->word, "put")==0) {
            lex_info = _lex(info);
            printf("%s", (char*)(intp_get_data(info, info->word)));
        }

        if(*info->data == '\0') break;
        lex_info = _lex(info);

    }

}
