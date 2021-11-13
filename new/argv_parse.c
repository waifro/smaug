#include <stdio.h>
#include <string.h>

#include "argv_parse.h"
#include "argv_variable.h"

char argv_stdin[256];

int ARGV_CompareArgv(char *buffer) {

    for (int n = 0; n < (short int)COUNT_OF(argv_argv); n++) {
        if (argv_argv[n] == NULL) continue;
        if (strcmp(buffer, argv_argv[n]) == 0) return (n);
    }

    return -1;
}

int ARGV_SegmentArgv(int argc, char *argv[]) {

    // no commands found
    if (argc == 1) {
        printf("# ARGV_SegmentArgv(): %s\n", argv_comment[0]); // would like to add a separated function for printf comment
        return -1;
    }

    int i;
    for (int n = 1; n < argc; n++) {

        i = ARGV_CompareArgv(argv[n]);

        if (i == 0 || i == 1) {
            printf("%s\n", argv_comment[2]);
            break;
        }

        else if (i == -1) {
            strncpy(argv_stdin, argv[n], 256);
            break;
        }
    }

    return 0;
}
