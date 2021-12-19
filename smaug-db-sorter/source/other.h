#ifndef OTHER_H
#define OTHER_H

extern char *CONSOLE_RED;
extern char *CONSOLE_GREEN;
extern char *CONSOLE_YELLOW;
extern char *CONSOLE_RESET;

char *strcpy_cinj(char *src, int index, char *ptr);
int strlen_ctok(const char *ptr, char tok);
size_t fdsize(int fd);
int strcmp_ctok(char *ptr, char tok);

#endif
