#define STB_DS_IMPLEMENTATION
#include "intp.h"

//////////////////////////////
//----------Logging-----------
//////////////////////////////

FILE *log;

void _warn(char *str) {
    // To do: time, line number, column number.
    fprintf(log, "%s\n", str);
}

int _error(char *str) {
    // To do: line number and coloured output.
    printf("%s\n", str);
    return -1;
}

//////////////////////////////
//----------Data Types--------
//////////////////////////////

void *intp_get_data(intp_info *info, char* name) {

    for(int i = 0; i < shlen(info->objs); i++) {
        if(!strcmp(name, info->objs[i].key)) {
            return info->objs[i].value;
        }
    }
}

void intp_set_data(intp_info *info, const char* name, void *value, bool is_constant) {

    shput(info->objs, (const char*)name, value);
}

//////////////////////////////
//----------Main--------------
//////////////////////////////

int intp_init(intp_info *info) {
    // Open the log file only when the interpreter is initialzed.
    log = fopen("report.log", "w");

    // Allocate both; 32 bytes should be enough; may be increased in future.
    info->tok  = (char*)malloc(sizeof(char)*32);
    info->word = (char*)malloc(sizeof(char)*32);

    info->objs = NULL;

    return (info->tok && info->word) ? 1 : 0;
}

int intp_free(intp_info *info) {

    fclose(log);

    shfree(info->objs);

    // Free if it is not empty.
    if(strlen(info->data) != 0) free(info->data);
    if(strlen(info->tok ) != 0) free(info->tok );
    if(strlen(info->word) != 0) free(info->word);
}

void intp_string(intp_info *info , char *str) {
    info->data = (char*)malloc(sizeof(char) * (strlen(str)+1));
    if(!info->data) {
        _error("Cannot allocate memory.");
    }

    size_t r = (size_t)strcpy(info->data, str); // Copy the content into the buffer.
    if(!r) {
        _error("Cannot read string.");
    }

    _parse(info);
}

void intp_file(intp_info *info, char *fn) {
    // To do: use 'intp_string()' internally.

    FILE *file = fopen(fn, "r");

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    info->data = (char*)malloc(sizeof(char) * size);

    if(!info->data) {
        _error("Cannot allocate memory.");
    }

    size_t r = fread(info->data, 1, size+1, file);
    if(!r) {
        _error("Cannot read file.");
    }

    fclose(file);
    strcat(info->data, "\0");
    _parse(info);
}
