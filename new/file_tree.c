#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "argv_global.h"
#include "file_tree.h"

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

int FILE_WriteOutput(const char *strin) {

    char output[] = "output.txt";
    FILE *fd;

    // check once on boot if file exists
    static bool check = false;
    if (check == false) {

        struct stat status;
        if (stat(output, &status) != 0) {
            // file doesnt exists, exit
            check = true;
        } else {
            // file exists, starts at zero, exit
            fd = fopen(output, "w");
            fclose(fd);
            check = true;
        }
    }

    fd = fopen(output, "a+");
    fprintf(fd, "%s", strin);
    fclose(fd);

    return 0;
}
