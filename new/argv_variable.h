#ifndef ARGV_VARIABLE_H
#define ARGV_VARIABLE_H

// curtesy of @SegFault42 :) Define to count nb element in char **
#define COUNT_OF(ptr) (sizeof(ptr) / sizeof((ptr)[0]))

#define DEBUG 1

extern char argv_strin[256];

// add more argvs (ex. files input out etc..)
extern char *argv_argv[256];

extern char *argv_comment[256];

#endif
