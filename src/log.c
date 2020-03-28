#include "intp.h"

FILE *logfile;

void intp_warn(intp_src_buf *buf, char *str) {
    fprintf(logfile, "Warning: Line %u, Column %u: %s\n", buf->line, buf->col, str);
}

int intp_error(intp_src_buf *buf, char *str) {
    printf("%s[%u, %u] Error: %s\n", buf->filename, buf->line, buf->col, str);
    exit(-1);
}

int intp_error_std(char *str, ...) {
    va_list args;
    printf("Fatal Error: ");
    va_start(args, str);
    printf("%s", va_arg(args, char*));
    va_end(args);
    printf("\n");
    exit(-1);
}