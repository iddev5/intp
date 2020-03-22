#include "intp.h"

FILE *logfile;

void intp_warn(intp_src_buf *buf, char *str) {
    fprintf(logfile, "Warning: Line %u, Column %u: %s\n", buf->line, buf->col, str);
}

int intp_error(intp_src_buf *buf, char *str) {
    printf("Error: Line %u, Column %u: %s\n", buf->line, buf->col, str);
    exit(-1);
}