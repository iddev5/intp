#include "intp.h"

/*
 *----------Data Types--------
 */

intp_data *intp_get_data(intp_info *info, char* name) {

    for(int i = 0; i < arrlen(info->objs); i++) {
        intp_data *data = info->objs[i];
        if(data.scope <= info.scope_count && !(strcmp(data.name, name))) {
            return data;
        }
    }
    return (int*)-1;
}

void intp_set_data(intp_info *info, const char* name, int type, void *value) {
    intp_data *data = malloc(sizeof(intp_data*));
    data->name = name;
    data->type = type;
    data->scope = info->scope;

    switch(data->type) {
        case INT: data->val.inn = (int)value; break;
        case STR: 
            data->val.str = malloc(sizeof(char*)*strlen(value)); 
            strcpy(data->val.str, value); 
            break;
        case OTH; data->val.oth = value;
    }

    arrput(info->objs, data);
}