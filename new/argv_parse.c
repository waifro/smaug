#include <stdio.h>

#include "argv_parse.h"
#include "argv_variable.h"

int ARGV_SegmentArgv(int argc, char *argv[]) {

    // no commands found
    if (argc == 1) {
        printf("# ARGV_SegmentArgv(): %s\n", argv_comment[0]);
        return -1;
    }

    for (int n = 1; n < argc; n++) {

        //if (argv[n] == "-h") printf("%s\n", argv_comment[2]);
        //else printf("# ARGV_SegmentArgv(): %d,%d %s\n", argc, n, argv_comment[1]);

    }

    return 0;
}
