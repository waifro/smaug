#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>

#include "db_core.h"
#include "db_dir.h"
#include "dir_operate.h"

int DBDIR_OperateFolder(char chr) {

    if (chr == 0) return -1;

    char *alpha[] = {
        "a-A", "b-B", "c-C", "d-D", "e-E", "f-F", "g-G", "h-H", "i-I",
        "j-J", "k-K", "l-L", "m-M", "n-N", "o-O", "p-P", "q-Q", "r-R",
        "s-S", "t-T", "u-U", "v-V", "w-W", "x-X", "y-Y", "z-Z", "numbers", "symbols"
    };

    if (isalnum(chr) != 0) {

        // digit detected
        if (isdigit(chr) != 0) {
            return 26;
        }

        // alpha detected
        else if (isalpha(chr) != 0) {
            for (int i = 0; i < 27; i++) {
                for (int n = 0; n < 3; n++) {
                    if (n == 1) continue;
                    if (alpha[i][n] == chr) return i;
                }
            }
        }

    } else return 27; // symbol/unknown detected

    return -1;
}

int DBDIR_CheckSortFolder(char chr) {

    char *alpha[] = {
        "a-A", "b-B", "c-C", "d-D", "e-E", "f-F", "g-G", "h-H", "i-I",
        "j-J", "k-K", "l-L", "m-M", "n-N", "o-O", "p-P", "q-Q", "r-R",
        "s-S", "t-T", "u-U", "v-V", "w-W", "x-X", "y-Y", "z-Z", "!numbers", "!symbols"
    };

    int result = DBDIR_OperateFolder(chr);
    if (result > -1) {
        const char *path = DBDIR_CreateFolder(alpha[result]);
        mkdir(path, 0777);
    } else if (result == -1) {
        printf("DBDIR_CheckSortFolder: error OperateFolder -1");
        return -1;
    } else if (result == -2) {
        printf("DBDIR_CheckSortFolder: error OperateFolder -2");
        return -1;
    }

    return result;
}

int DBDIR_CheckAlphaStructure(char *ptr, char *result) {

    char *alpha[] = {
        "a-A", "b-B", "c-C", "d-D", "e-E", "f-F", "g-G", "h-H", "i-I",
        "j-J", "k-K", "l-L", "m-M", "n-N", "o-O", "p-P", "q-Q", "r-R",
        "s-S", "t-T", "u-U", "v-V", "w-W", "x-X", "y-Y", "z-Z", "!numbers", "!symbols"
    };

    // check if sort alpha/num folder exists
    int res = DBDIR_CheckSortFolder(ptr[0]);
    if (res == -1) return -1;

    // opening cw directory
    sprintf(result, "%s\\%s", dbcore_startf, alpha[res]);

    return 0;
}

int DBDIR_CopyRootFolder(char *folder) {
    char buffer[256];
    //DIR_BlenchFolder(folder);
    sprintf(buffer, "%s\\db-sort", folder);
    strncpy(dbcore_startf, buffer, 256);
    return 0;
}

// return -1 on error; 0 on success
int DBDIR_CheckFolder(char *folder) {
    struct stat st = {0};
    if (stat(folder, &st) == 0) {
        return 0;
    } else return -1;
}

const char *DBDIR_CreateFolder(char *folder) {
    static char dirfolder[256] = {0};
    sprintf(dirfolder, "%s\\%s", dbcore_startf, folder);
    return (dirfolder);
}
