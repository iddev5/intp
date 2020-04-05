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
    info->scope = 0; /* Global scope */

    return (info->buf->tok) ? 1 : 0;
}

void intp_free(intp_info *info) {
    /* Dellocate everything */
    
    /* Close the log file */
    fclose(logfile);

    /* Free all the intp_data */
    for(int i=0; i<stbds_arrlen(info->objs); i++) {
        if(info->objs[i]->type == STR_T) { free(info->objs[i]->val.str); }
        free(info->objs[i]->name);
        free(info->objs[i]);
    }
    stbds_arrfree(info->objs);

    /* Free intp_buf */
    if(info->buf->input == INPUT_STRING && strlen(info->buf->data) != 0) { free(info->buf->data); }
    else if(info->buf->input == INPUT_FILE) { fclose(info->buf->file); }
    free(info->buf->tok);
    free(info->buf->filename);
    free(info->buf);

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
    info->buf->input = INPUT_STRING;
    intp_interp(info->buf, info);
}

void intp_file(intp_info *info, char *fn) {
    FILE *file = fopen(fn, "r");
    if(file == NULL) {
        intp_error_std("Cannot open input file: ", fn);
    }

    info->buf->file = file;
    info->buf->filename = NEW_STRING(fn);
    info->buf->input = INPUT_FILE;
    info->buf->th = fgetc(info->buf->file);

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

#ifdef __TINYC__
    /* For supporting tcc */
    void __dso_handle(void) { }
#endif