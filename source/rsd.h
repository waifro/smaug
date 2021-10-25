#ifndef RSD_H
#define RSD_H

extern DIR* rsd_directory[255];
extern struct dirent* rsd_struct;
extern struct stat rsd_stat;
extern int rsd_pos;
extern char rsd_cwdir[255];


void rsd_dirpath(char *cwdir, char *dir, char *result);
void rsd_gobackdir(char *dest);

int rsd_lastopen(void);
void rsd_close(void);
void rsd_closeall(void);
bool rsd_open(char *dir);
int rsd_read(char *result);

#endif
