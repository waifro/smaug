#ifndef ARGV_PARSE_H
#define ARGV_PARSE_H

// curtesy of @SegFault42 :) Define to count nb element in char **
#define COUNT_OF(ptr) (sizeof(ptr) / sizeof((ptr)[0]))

int ARGV_CompareArgv(char *buffer);
int ARGV_SegmentArgv(int argc, char *argv[]);

#endif
