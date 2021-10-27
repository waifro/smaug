#ifndef RAS_H
#define RAS_H

extern FILE *ras_fd;
extern char ras_head[10];
extern char ras_tail[10];
extern int ras_len;

int ras_checkparameters(void);
int ras_checkargv(int argc, char **argv, char *result);
int ras_openfile(char *path);
void ras_closefile(void);
void ras_findargv(char *file, char *text);

#endif
