#include <stdio.h>

#include "dir_tree.h"
#include "dir_operate.h"

void CORE_Testing(void) {

    char folder[256];
    getcwd(dir_startf, 256);
    strcpy(folder, dir_startf);

    if (DIR_OpenFolder(folder, 1) != 0) { perror("# DIR_OpenFolder()"); return; }

    printf("\ncwd: %s\n", folder);

    int isfolder = -1;
    while(1) {

        printf("\n3: [%d] %s\n", dir_subf, folder);

        while(1) {

            if (DIR_ReadFolder(folder) != 0) {
                perror("# DIR_ReadFolder()");
                DIR_CloseFolder();
                isfolder = -1;
                break;
            }

            printf("\n4: [%d] %s\n", dir_subf, dir_cwbuffer);

            isfolder = DIR_IsFolder(dir_cwbuffer);
            if (isfolder >= 0) {

                if (isfolder == 0) {
                    printf("File: %s\n", dir_cwbuffer);
                }

                // skips ".."
                else if (isfolder == 1 && dir_struct->d_name[0] != '.') {
                    printf(" Dir: %s\n", dir_cwbuffer);
                    strcpy(folder, dir_cwbuffer);

                    printf("\n1: [%d] %s\n", dir_subf, folder);

                    break;
                }

            } else break;

        }

        printf("\n2: [%d] %s\n", dir_subf, dir_cwbuffer);

        if (DIR_OpenFolder(folder, 0) != 0) perror("# DIR_OpenFolder()");
        if (isfolder < 0 && dir_subf < 0) break;
    }

    return;
}
