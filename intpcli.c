#include <stdio.h>
#include <stdlib.h>

#include "src/intp.h"

intp_info info;

void intp_at_exit() {
    intp_free(&info);
}

int main(int argc, char **argv) {

	if(argc < 2) {
        printf("Usage: INTP filename.intp\n");
        exit(-1);
	}

    atexit(intp_at_exit);
    
    if(intp_init(&info)) {
        intp_file(&info, argv[1]);
    }
}
