#include <stdio.h>
#include <errno.h>
#include "argv_parse.h"

#include "dir_tree.h"
#include "dir_operate.h"

void CORE_StartSequence(int argc, char *argv[]) {

    if (ARGV_SegmentArgv(argc, argv) != 0) return;

    /*
    char folder[256];
    getcwd(dir_startf, 256);
    strcpy(folder, dir_startf);

    if (DIR_OpenFolder(folder, 1) != 0) { perror("# DIR_OpenFolder()"); return; }

    printf("\ncwd: %s\n", folder);

    int isfolder = -1;
    while(1) {

        while(1) {

            if (DIR_ReadFolder(folder) != 0) {

                if (errno != 0) perror("# DIR_ReadFolder()");
                else printf("Close dir: %s\n", folder);

                DIR_CloseFolder(folder);
                isfolder = -1;
                break;
            }

            isfolder = DIR_IsFolder(dir_cwbuffer);
            if (isfolder >= 0) {

                if (isfolder == 0) {
                    printf("File: %s\n", dir_cwbuffer);
                }

                // skips ".."
                else if (isfolder == 1 && dir_struct->d_name[0] != '.') {
                    printf(" Dir: %s\n", dir_cwbuffer);
                    strcpy(folder, dir_cwbuffer);

                    if (DIR_OpenFolder(folder, 0) != 0) perror("# DIR_OpenFolder()");

                }

            } else break;

        }

        if (isfolder < 0 && dir_subf < 0) break;
    }
    */

    return;
}
