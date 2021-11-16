#include <stdio.h>

#include "argv_variable.h"
#include "file_operate.h"

FILE *FILE_OpenFile(char *pathfile) {

    FILE *stream = NULL;
    stream = fopen(pathfile, "r");
    if (stream == NULL) return NULL;

    if (DEBUG == 1) printf("# FILE_OpenFile(): stream: %p\n", stream);

    return stream;
}

int FILE_CloseFile(FILE *stream) {

    if (fclose(stream) == EOF) {
        stream = NULL;
    } else return -1;

    return 0;
}

// strout: copy buf to strout
int FILE_ReadFile(FILE *stream, char *strout) {

    char buf[256];
    if (fgets(buf, 256, stream) == NULL) return -1;

    if (DEBUG == 1) printf("# FILE_ReadFile(): stream: %p\n", stream);

    if (feof(stream) != 0) return -2;
    if (strlen(buf) > 254) return -3;

    strcpy(strout, buf);

    return 0;
}
