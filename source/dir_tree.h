#ifndef DIR_TREE_H
#define DIR_TREE_H

#include <dirent.h>

// buffer for writing current filename
extern char dir_cwbuffer[1024];
// dir_startf is the directories starting point
extern char dir_startf[256];
// dir_tree is all stream subdirs
extern DIR *dir_tree[256];
// dir_subf keeps track of stream dir_tree
extern int dir_subf;
// optional for external usage
extern struct dirent *dir_struct;

int DIR_OpenFolder(char *pathdir, int init);
int DIR_ReadFolder(char *pathdir);
int DIR_CloseFolder(char *pathdir);

#endif
