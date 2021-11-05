#include <stdio.h>

#include "dir_tree.h"
#include "dir_operate.h"

void CORE_Testing(void) {

    char folder[256];
    DIR_OperativeTree(folder);

    printf("cwd: %s\n", folder);

    int isfolder = -1;
    while(1) {

        if (isfolder < 0 && dir_subf < 0) break;
        if (DIR_OpenFolder(folder) != 0) perror("# DIR_OpenFolder()");

        printf("\n%s\n", dir_cwbuffer);

        while(1) {

            if (DIR_ReadFolder() != 0) {
                perror("# DIR_ReadFolder()");
                DIR_CloseFolder();
                break;
            }

            isfolder = DIR_IsFolder(NULL);
            if (isfolder >= 0) {

                if (isfolder == 0) {
                    printf("File: %s\n", dir_cwbuffer);
                }

                // skips ".."
                else if (isfolder == 1 && dir_struct->d_name[0] != '.') {
                    printf(" Dir: %s\n", dir_cwbuffer);
                    strcpy(folder, dir_cwbuffer);

                    printf("\n1: %s\n", folder);

                    break;
                }

            } else break;

        }

    }

    return;
}
