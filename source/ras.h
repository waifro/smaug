#ifndef RAS_H
#define RAS_H

void ras_checkargv(void);
int ras_openfile(char *path);
void ras_closefile(void);
void ras_findargv(char *file, char *text);

#endif
