#include <stdio.h>
#include <stdlib.h>

#include "intp.h"

int main(int argc, char **argv) {

	if(argc < 2) {
        printf("Usage: INTP filename.intp\n");
        exit(-1);
	}

	int r;
    intp_info info;

    r = intp_init(&info);
    if(r) intp_file(&info, argv[1]);

	intp_free(&info);
}
