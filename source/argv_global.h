#ifndef ARGV_GLOBAL_H
#define ARGV_GLOBAL_H

// curtesy of @SegFault42 :) Define to count nb element in char **
#define COUNT_OF(ptr) (sizeof(ptr) / sizeof((ptr)[0]))

#define DEBUG 0

extern char argv_strin[256];

// add more argvs (ex. files input out etc..)
extern char *argv_argv[256];

extern char *argv_comment[256];

#endif
