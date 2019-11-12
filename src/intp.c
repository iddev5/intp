#include "intp.h"

//////////////////////////////
//----------Main--------------
//////////////////////////////

int intp_init(intp_info *info) {

    info->tok  = (char*)malloc(sizeof(char)*32);
    info->word = (char*)malloc(sizeof(char)*32);

    //*result |= (info->tok && info->word) ? 1 : 0;

    return (info->tok && info->word) ? 1 : 0;
}

int intp_free(intp_info *info) {
    free(info->data);
    free(info->tok );
    free(info->word);
}

void intp_string(intp_info *info , char *str) {
    info->data = (char*)malloc(sizeof(char) * (strlen(str)+1));
    if(!info->data) {
        intp__error("Cannot allocate memory.");
    }

    size_t r = (size_t)strcpy(info->data, str);
    if(!r) {
        intp__error("Cannot read string.");
    }

    intp__parse(info);
}

void intp_file(intp_info *info, char *fn) {

    FILE *file = fopen(fn, "r");

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    printf("file size: %ld\n", size);

    info->data = (char*)malloc(sizeof(char) * size);

    if(!info->data) {
        intp__error("Cannot allocate memory.");
    }

    size_t r = fread(info->data, 1, size+1, file);
    if(!r) {
        intp__error("Cannot read file.");
    }

    fclose(file);
    strcat(info->data, "\0");
    intp__parse(info);
}
