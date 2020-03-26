#include "intp.h"

intp_data *intp_get_data(intp_info *info, char* name) {
    for(int i = 0; i < stbds_arrlen(info->objs); i++) {
        intp_data *data = info->objs[i];
        if(data->scope <= info->scope && !(strcmp(data->name, name))) {
            return data;
        }
    }
    return (intp_data*)-1;
}

void intp_set_data(intp_info *info, const char* name, int type, void *value) {
    intp_data *data = NEW_DATA(name, type, value);
    intp_set_data_from(info, data);
}

void intp_set_data_from(intp_info *info, intp_data *data) {
    data->scope = info->scope;

    for(int i=0; i < stbds_arrlen(info->objs); i++) {
        intp_data *this = info->objs[i];
        if(!strcmp(this->name, data->name)) {
            info->objs[i] = data; return;
        }
    }

    stbds_arrput(info->objs, data);
}

/* Private Functions */

intp_data *NEW_DATA(const char *name, int type, void *value) {
    intp_data *data = ALLOC(intp_data*, 1);
    strcpy(data->name, name);
    data->type = type;

    switch(data->type) {
        case NUM_T: { 
            real_t *num = ALLOC(real_t, 1);
            num = (real_t*)value;
            data->val.num = *num;
            break; 
        }

        case STR_T: {
            data->val.str = NEW_STRING(value);
            break;
        }
    }

    return data;
}