#include "intp.h"

/*
 *----------Data Types--------
 */

void *intp_get_data(intp_info *info, char* name) {

    for(int i = 0; i < shlen(info->objs); i++) {
        if(!strcmp(name, info->objs[i].key)) {
            return info->objs[i].value;
        }
    }
    return (int*)-1;
}

void intp_set_data(intp_info *info, const char* name, void *value, bool is_constant) {

    shput(info->objs, (const char*)name, value);
}