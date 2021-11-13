#ifndef ARGV_VARIABLE_H
#define ARGV_VARIABLE_H

// curtesy of @SegFault42 :) Define to count nb element in char **
#define COUNT_OF(ptr) (sizeof(ptr) / sizeof((ptr)[0]))

extern char argv_stdin[256];

// add more argvs (ex. files input out etc..)
char *argv_argv[256] = {
    "-h",
    "--help"
};

char *argv_comment[256] = {
    "no argv, use '-h' next time.",
    "invalid command",
    "usage: smaug <argv_to_search> | ex. \"smaug helloworld\""
};

#endif
