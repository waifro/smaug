#include <stdio.h>

#include "core.h"
#include "argv_global.h"

char argv_strin[256];
char *argv_argv[256] = { "-h", "--help" };
char *argv_comment[256] = { "no argv, use '-h' next time.", "invalid command", "usage: smaug <argv_to_search> | ex. \"smaug helloworld\"" };

int main (int argc, char *argv[]) {
    (void)argc; (void)argv;

    CORE_StartSequence(argc, argv);

    return 0;
}
