#include <stdio.h>
#include <sys/stat.h>

#include "db_file.h"

int DBFILE_CheckFile(char *filename) {
    struct stat st;
    if (stat(filename, &st) == -1) {
        fopen(filename, "w");
    } else return -1;

    return 0;
}
