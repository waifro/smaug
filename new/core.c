#include <stdio.h>

#include "dir_tree.h"
#include "dir_operate.h"

void CORE_Testing(void) {

    char folder[256];
    getcwd(dir_startf, 256);
    strcpy(folder, dir_startf);

    printf("cwd: %s\n", folder);

    int isfolder = -1;
    while(1) {

        if (isfolder < 0 && dir_subf < 0) break;
        if (DIR_OpenFolder(folder) != 0) perror("# DIR_OpenFolder()");

        printf("\n2: %s\n", folder);
        printf("\n3: %s\n", dir_cwbuffer);

        while(1) {

            if (DIR_ReadFolder(folder) != 0) {
                perror("# DIR_ReadFolder()");
                DIR_CloseFolder();
                break;
            }

            printf("\n4: %s\n", dir_cwbuffer);

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
