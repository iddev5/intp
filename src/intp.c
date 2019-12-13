#define STB_DS_IMPLEMENTATION
#include "intp.h"

//////////////////////////////
//----------Logging-----------
//////////////////////////////

FILE *logfile;

void intp_warn(intp_src_buf *buf, char *str) {
    fprintf(logfile, "Warning: Line %u, Column %u: %s\n", buf->line, buf->col, str);
}

int intp_error(intp_src_buf *buf, char *str) {
    printf("Error: Line %u, Column %u: %s\n", buf->line, buf->col, str);
    exit(-1);
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
    return (int*)-1;
}

void intp_set_data(intp_info *info, const char* name, void *value, bool is_constant) {

    shput(info->objs, (const char*)name, value);
}

//////////////////////////////
//----------Main--------------
//////////////////////////////

int intp_init(intp_info *info) {
    // Open the log file only when the interpreter is initialzed.
    logfile = fopen("report.log", "w");

    info->objs = NULL;
    info->buf  = malloc(sizeof(intp_src_buf));

    // Allocate into_info.tok; 32 bytes should be enough; may be increased in future.
    info->buf->tok  = (char*)malloc(sizeof(char)*32);

    return (info->buf->tok) ? 1 : 0;
}

void intp_free(intp_info *info) {

    fclose(logfile);

    shfree(info->objs);

    // Free if it is not empty.
    if(strlen(info->buf->data) != 0) free(info->buf->data);
    if(strlen(info->buf->tok ) != 0) free(info->buf->tok );
}

void intp_string(intp_info *info , char *str) {
    info->buf->data = (char*)malloc(sizeof(char) * (strlen(str)+1));
    if(!info->buf->data) {
        printf("Cannot allocate memory.");
    }

    size_t r = (size_t)strcpy(info->buf->data, str); // Copy the content into the buffer.
    if(!r) {
        printf("Cannot read string.");
    }

    _parse(info);
}

void intp_file(intp_info *info, char *fn) {

    FILE *file = fopen(fn, "r");
    
    if(feof(file)) {
        printf("Cannot open file: %s\n", fn);
        exit(-1);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    info->buf->data = (char*)malloc(sizeof(char) * size);

    if(!info->buf->data) {
        printf("Cannot allocate memory.\n");
        exit(-1);
    }

    size_t r = fread(info->buf->data, 1, size+1, file);
    if(!r) {
        printf("Cannot read file.\n");
        exit(-1);
    }

    fclose(file);
    strcat(info->buf->data, " \0");
    _parse(info);
}
