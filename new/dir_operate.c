#include <stdbool.h>
#include <stddef.h>
#include <errno.h>
#include <sys/stat.h>

#include "dir_tree.h"
#include "dir_operate.h"

int DIR_OperativeTree(char *buffer) {

    getcwd(buffer, 256);
    if (buffer == NULL) { perror("#"); return -2; }

    return 0;
}

int DIR_IsFolder(char *pathname) {

    struct stat format;
    if (pathname == NULL) if (stat(dir_struct->d_name, &format) != 0) { perror(""); return -1; }
    else if (pathname != NULL) if (stat(pathname, &format) != 0) { perror(""); return -2; }

    if (S_ISDIR(format.st_mode) == true) return 1;
    else return 0;
}

/*
int DIR_BlenchFolder(char *pathdir) {

    int strlength = strlen(pathdir);
    for (int n = strlength; n > 0; n--) {
        if (cwdir[n] == '\') { dir_startf[n] = '\0'; return 0; }
    }

    return -1;
}
*/
