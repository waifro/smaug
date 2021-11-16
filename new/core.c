#include <stdio.h>
#include <errno.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>

#include "file_tree.h"
#include "file_operate.h"

#include "argv_parse.h"
#include "argv_global.h"

#include "dir_tree.h"
#include "dir_operate.h"

const char *CORE_ConjoinOutput(char *strin, int line) {

    static char result[512] = {0};
    sprintf((char*)result, "File: %s [line:%d] %s", dir_cwbuffer, line, strin);

    return (result);
}

void CORE_StartSequence(int argc, char *argv[]) {

    if (ARGV_SegmentArgv(argc, argv) != 0) return;

    char folder[256];
    getcwd(dir_startf, 256);
    strcpy(folder, dir_startf);

    if (DIR_OpenFolder(folder, 1) != 0) { if (DEBUG == 1) perror("# DIR_OpenFolder()"); return; }

    if (DEBUG == 1) printf("\ncwd: %s\nargv_strin: %s\n", folder, argv_strin);

    int isfolder = -1;
    while(1) {

        while(1) {

            if (DIR_ReadFolder(folder) != 0) {

                if (errno != 0) { if (DEBUG == 1) perror("# DIR_ReadFolder()"); }
                else printf("Close dir: %s\n", folder);

                DIR_CloseFolder(folder);
                isfolder = -1;
                break;
            }

            isfolder = DIR_IsFolder(dir_cwbuffer);
            if (isfolder >= 0) {

                if (isfolder == 0) {
                    printf("File: %s\n", dir_cwbuffer);

                    FILE *fd = NULL; char buf[256];
                    if ((fd = FILE_OpenFile(dir_cwbuffer)) == NULL) { if (DEBUG == 1) perror("# FILE_OpenFile()"); break; }

                    for (int n = 1; ; n++) {
                        if (FILE_ReadFile(fd, buf) != 0) { if (DEBUG == 1) perror("# FILE_ReadFile()"); break; }
                        if (FILE_SearchString(argv_strin, buf) == -1) FILE_WriteOutput(CORE_ConjoinOutput(buf, n));
                    }

                    FILE_CloseFile(fd);
                }

                // skips "." (bug: skips even hidden files)
                else if (isfolder == 1 && dir_struct->d_name[0] != '.') {
                    printf(" Dir: %s\n", dir_cwbuffer);
                    strcpy(folder, dir_cwbuffer);

                    if (DIR_OpenFolder(folder, 0) != 0) { if (DEBUG == 1) perror("# DIR_OpenFolder()"); }

                }

            } else break;

        }

        if (isfolder < 0 && dir_subf < 0) break;
    }

    return;
}
