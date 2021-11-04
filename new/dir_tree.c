#include <stdio.h>
#include <string.h>
#include "dir_tree.h"

//char dir_startf[256];
DIR *dir_tree[256];
int dir_subf;
struct dirent *dir_struct;

int DIR_OpenFolder(char *pathdir) {

    dir_tree[dir_subf] = opendir(pathdir);
    if (&dir_tree[dir_subf] == NULL) return -2;

    // if as been opened the folder, keep track of stream
    dir_subf++;
    if (dir_subf >= 255) return -1;

    return 0;
}

int DIR_ReadFolder(void) {

    dir_struct = readdir(dir_tree[dir_subf]);
    if (dir_struct == NULL) {
        perror(""); return -1; }

    return 0;
}

int DIR_CloseFolder(char *pathdir) {

    if (dir_tree[dir_subf] != NULL) {
        closedir(dir_tree[dir_subf]);
        dir_tree[dir_subf] = NULL;
    }

    // go back anyways; if still zero then stream dir is still OK
    dir_subf--;
    if (dir_subf <= -1) return -1;

    return 0;
}
