#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <dirent.h>

// dir_tree is all subdirs
extern DIR dir_tree[256];
extern int dir_subf;

int DIR_OperateFolder(void);

int DIR_OpenFolder(char *pathdir);
int DIR_BlenchFolder(char *cwdir);
int DIR_CloseFolder(char *cwdir);

void DIR_Testing(void);

#endif
