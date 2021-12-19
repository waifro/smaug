#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "other.h"
#include "db_core.h"
#include "db_dir.h"
#include "dir_tree.h"
#include "dir_operate.h"

void CORE_Testing(void) {

    char folder[512];
    getcwd(dir_startf, 512);
    strcpy(folder, dir_startf);

    if (DIR_OpenFolder(folder, 1) != 0) {
        perror("# DIR_OpenFolder()"); return;
    }

    // copy root directory to dbcore_startf
    DBDIR_CopyRootFolder(dir_startf);
    printf("DBDIR_CopyRootFolder %s\n", dbcore_startf);

    printf("\ncwd: %s\n", folder);

    int isfolder = -1;
    while(1) {

        while(1) {

            if (DIR_ReadFolder(folder) != 0) {

                if (errno != 0) {
                    printf("\t# error: %s\n", folder);
                    perror("\t# DIR_ReadFolder()");
                    return;
                }
                else printf("\nClose dir: %s\n", folder);

                DIR_CloseFolder(folder);
                isfolder = -1;
                break;
            }

            isfolder = DIR_IsFolder(dir_cwbuffer);
            if (isfolder >= 0) {

                if (isfolder == 0) {

                    // starts the magic *^*
                    printf("\nFile: %s\n", dir_cwbuffer);

                    int ind = strlen_ctok(dir_cwbuffer, '.');

                    // everything is correct
                    if (ind != (int)strlen(dir_cwbuffer) || ind != -1) {

                        if (strcmp(&dir_cwbuffer[ind], ".txt") == 0) {

                            FILE *fp = fopen(dir_cwbuffer, "r");
                            if (!fp) {
                                printf("\n\t>>%s error: %d opening file: %s%s\n", CONSOLE_RED, errno, dir_cwbuffer, CONSOLE_RESET);
                                break;
                            }

                            // reading file
                            char buffer[512]; int count = 0; bool check = false;
                            while(fgets(buffer, 512, fp) != NULL) {

                                count++;

                                int res = strcmp_ctok(buffer, ':');
                                if (res == -1) {
                                    if ((res = strcmp_ctok(buffer, ';')) == -1) {
                                        printf("\r\tline: %d", count);
                                        printf("\t>> error: not valid string, check it yourself\n\n");
                                        check = true;
                                    }
                                }

                                int result = DBCORE_StartSequence(buffer);

                                if (result == -1) {
                                    printf("\n\t>>%s error: DBCORE_StartSequence at %d line%s", CONSOLE_RED, count, CONSOLE_RESET);
                                    exit(-1);
                                } else if (result == -2) {
                                    printf("\n\t>>%s warning: safe to delete file manually%s", CONSOLE_YELLOW, CONSOLE_RESET);
                                    check = true;
                                } else if (result == 0) {
                                    printf("\r\tline: %d", count);

                                } else printf("\nwtf just happend");
                            }

                            fclose(fp);

                            if (check == false) {
                                printf("\t>>%s successfully sorted file, removing...%s\n", CONSOLE_GREEN, CONSOLE_RESET);
                                //remove(dir_cwbuffer);
                            }

                        } else {
                            printf("\t>> error: not a text file *.txt\n");
                        }
                    }
                }

                // skips ".."
                else if (isfolder == 1 && (strcmp(dir_struct->d_name, ".") != 0 && strcmp(dir_struct->d_name, "..") != 0)) {

                    // dont know the behavior (might be stuck in a loop)
                    //if (strcmp(dir_cwbuffer, dbcore_startf) != 0 && strcmp(dir_cwbuffer, dir_startf) != 0) {
                    if (strcmp(dir_cwbuffer, dbcore_startf) != 0) {

                        printf(" Dir: %s\n", dir_cwbuffer);
                        strcpy(folder, dir_cwbuffer);

                        if (DIR_OpenFolder(folder, 0) != 0) perror("# DIR_OpenFolder()");
                    }

                }

            } else break;

        }

        if (isfolder < 0 && dir_subf < 0) break;
    }

    return;
}
