#define STB_DS_IMPLEMENTATION
#include "intp.h"

FILE *logfile;

int intp_init(intp_info *info) {
    /* Open the log file when the interpreter is initialzed. */
    logfile = fopen("report.log", "w");
    if(logfile == NULL) {
        intp_error_std("Cannot create/open log file: report.log");
    }

    /* Memory will be handled by stb_ds */
    info->objs = NULL;
    
    /* Initial allocation */
    info->buf = ALLOC(intp_src_buf, 1);
    info->buf->tok = ALLOC(char*, 19);
    if(info->buf == NULL || info->buf->tok == NULL) {
        intp_error_std("Cannot allocate memory for source buffer");
    }

    info->buf->line = info->buf->col = 1;

    return (info->buf->tok) ? 1 : 0;
}

void intp_free(intp_info *info) {
    /* Dellocate everything */
    fclose(logfile);
    stbds_arrfree(info->objs);

    /* Free if it is not empty. */
    if(strlen(info->buf->data) != 0) { free(info->buf->data); }
    if(strlen(info->buf->tok ) != 0) { free(info->buf->tok ); }
    if(info->buf != NULL) { free(info->buf); }

#ifdef INTP_DEBUG
    printf("Dellocation completed.\n");
#endif
}

void intp_string(intp_info *info , char *str) {
    info->buf->data = ALLOC(char*, strlen(str)+1);
    if(info->buf->data == NULL) {
        intp_error_std("Cannot allocate memory for source buffer");
    }

    /* Copy the content into the buffer. */
    if(!strcpy(info->buf->data, str)) {
        intp_error_std("Cannot read input string");
    }

    info->buf->filename = NEW_STRING("<string>");
    intp_interp(info->buf, info);
}

void intp_file(intp_info *info, char *fn) {
    FILE *file = fopen(fn, "r");
    if(file == NULL) {
        intp_error_std("Cannot open input file: ", fn);
    }

    /* Get the size of the file */
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    /* Check the size */
    if(size <= 0) {
        intp_error_std("Fatal Error: Invalid size of input file: ", fn);
    }

    /* Allocate memory */
    info->buf->data = ALLOC(char*, size);
    if(info->buf->data == NULL) {
        intp_error_std("Cannot allocate memory");
    }

    /* Read the file content and copy to buffer */
    if(!fread(info->buf->data, 1, size+1, file)) {
        intp_error_std("Cannot read input file");
    }

    fclose(file);
    info->buf->data[size+1] = '\0'; /* Append NULL termination */
    info->buf->filename = NEW_STRING(fn);
    intp_interp(info->buf, info);
}

/* Private Functions */

char *NEW_STRING(const char *str) {
    char *new = ALLOC(char*, strlen(str));
    if(new == NULL) {
        intp_error_std("Couldn't allocate memory for arbitary string");
    }
    strcpy(new, str);
    return new;
}
