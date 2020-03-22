#include "intp.h"

intp_data *intp_get_data(intp_info *info, char* name) {
    for(int i = 0; i < arrlen(info->objs); i++) {
        intp_data *data = info->objs[i];
        if(data->scope <= info->scope_count && !(strcmp(data->name, name))) {
            return data;
        }
    }
    return (intp_data*)-1;
}

void intp_set_data(intp_info *info, const char* name, int type, void *value) {
    intp_data *data = new_data(name, type, value);
    data->scope = info->scope_count;
    arrput(info->objs, data);
}

void intp_set_dataEx(intp_info *info, intp_data *data) {
    data->scope = info->scope_count;
    arrput(info->objs, data);
}

/* Private Functions */

intp_data *new_data(const char *name, int type, void *value) {
    intp_data *data = malloc(sizeof(intp_data*));
    strcpy(data->name, name);
    data->type = type;

    switch(data->type) {
        case INT: { 
            int64_t *inn = (int64_t*)value;
            data->val.inn = *inn;
            break; 
        }
        case STR: 
            data->val.str = malloc(sizeof(char*)*strlen(value)); 
            strcpy(data->val.str, value); 
            break;
        case OTH: data->val.oth = value;
    }

    return data;
}