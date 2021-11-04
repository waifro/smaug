#include <stdio.h>
#include "directory.h"

char dir_startf[256];
DIR dir_tree[256];
int dir_subf;

int DIR_OperativeFolder(void) {

    getcwd(dir_startf, 256);

    return 0;
}

int DIR_IsFolder(void) {

    return 0;
}

int DIR_OpenFolder(char *pathdir) {

    dir_subf++;
    if (dir_subf >= 255) return -1;

    dir_tree[dir_subf] = opendir(pathdir);

    return 0;
}

int DIR_BlenchFolder(char *cwdir) {

    for (int n = 256; n > 0; n--) {
        if (cwdir[n] == '\') { dir_startf[n] = '\0'; return 0; }
    }

    return -1;
}

int DIR_CloseFolder(char *cwdir) {

    if (dir_tree[dir_subf] != NULL) {
        closedir(dir_tree[dir_subf]);
        dir_tree[dir_subf] = NULL;
    }

    dir_subf--;
    if (dir_subf <= -1) return -1;

    if (DIR_ReturnOpenFolder(cwdir);

    return 0;
}

void DIR_Testing(void) {

    printf("bruh");

    return;
}
