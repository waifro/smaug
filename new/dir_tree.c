#include <stdio.h>
#include <string.h>
#include "dir_tree.h"
#include "dir_operate.h"

char dir_cwbuffer[256];
char dir_startf[256];
DIR *dir_tree[256];
int dir_subf;
struct dirent *dir_struct;

int DIR_OpenFolder(char *pathdir, int init) {

    // if asnt still been opened the folder, keep track of stream
    if (strcmp(pathdir, dir_startf) != 0) dir_subf++;
    else if (strcmp(pathdir, dir_startf) == 0 && init == 0) return -1;

    if (dir_subf >= 255) return -2;

    dir_tree[dir_subf] = opendir(pathdir);
    if (dir_tree[dir_subf] == NULL) return -3;

    return 0;
}

int DIR_ReadFolder(char *pathdir) {

    dir_struct = readdir(dir_tree[dir_subf]);
    if (dir_struct == NULL) return -1;

    sprintf(dir_cwbuffer, "%s\\%s", pathdir, dir_struct->d_name);

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

    if (DIR_BlenchFolder(pathdir) != 0) return -2;

    return 0;
}
