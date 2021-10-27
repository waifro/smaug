#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>

#include "rsd.h"
#include "ras.h"

FILE *ras_fd = NULL;
char ras_head[10];
char ras_tail[10];
int ras_len;

int ras_checkparameters(void) {

    if (strlen(ras_head) != 0) {
        if (strlen(ras_tail) == 0) {
            printf("missing tail parameter\n");
            return -1;
        } else if (ras_len == 0) {
            printf("missing length parameter\n");
            return -1;
        }
    } else if (strlen(ras_tail) != 0) {
        if (strlen(ras_head) == 0) {
            printf("missing head parameter\n");
            return -1;
        } else if (ras_len == 0) {
            printf("missing length parameter\n");
            return -1;
        }
    } else if (ras_len != 0) {
        if (strlen(ras_tail) == 0) {
            printf("missing tail parameter\n");
            return -1;
        } else if (strlen(ras_head) == 0) {
            printf("missing head parameter\n");
            return -1;
        }
    }

    return 0;
}

int ras_checkargv(int argc, char **argv, char *result) {

    if (argc < 2) {
        printf("no command found, use '-h' or '--help' next time.\n");
        return -1;
    }

    if (argv[1][0] != '-') {
        strcpy(result, argv[1]);
        return 0;
    }

    char commands[9][10] = {"-e", "--head", "-t", "--tail", "-l", "--length", "-h", "--help" };

    for (int n = 1; n < argc; n++) {

        if (argv[n][0] != '-') continue;

        for (int i = 0; i < 8; i++) {

            if (strcmp(commands[i], argv[n]) == 0) {

                n++;

                if (i == 0 || i == 1) {
                    strcpy(ras_head, argv[n]);
                    printf("head: %s\n", ras_head);
                    break;
                } else if (i == 2 || i == 3) {
                    strcpy(ras_tail, argv[n]);
                    printf("tail: %s\n", ras_tail);
                    break;
                } else if (i == 4 || i == 5) {
                    ras_len = atoi(argv[n]);
                    printf("length: %d\n", ras_len);
                    break;
                } else if (i == 6 || i == 7) {
                    printf("see readme on github\n");
                    return -1;
                }
            }
        }
    }

    if (ras_checkparameters() != 0) return -1;

    int length = strlen(ras_head) + strlen(ras_tail);

    for (int n = 0; n <= length; n++) {
        if (n == 0) { strcpy(result, ras_head); n += strlen(ras_head); }
        else if ((n + strlen(ras_tail)-1) == length) { strcat(result, ras_tail); break; }
        else strcat(result, "#");
    }

    return 0;
}

int ras_openfile(char *path) {

    if (strlen(path) <= 1 || path == NULL) return -1;

    ras_fd = fopen(path, "r");
    if (ras_fd == NULL) return -2;

    return 0;
}

void ras_closefile(void) {
    fclose(ras_fd);
    return;
}

void ras_findargv(char *file, char *search) {

    if (ras_openfile(file) != 0) return;

    char buffer[255];
    int length_buf; int count = 0;
    bool door_once = false;

    while(1) {

        if (fgets(buffer, 255, ras_fd) == NULL) break;

        length_buf = strlen(buffer) - 1;
        for (int n = 0; n < length_buf; n++) {

            if(door_once == true) {
                if (search[count] == '#') {
                    count++;
                    continue;
                }

                if (search[count] != buffer[n]) {
                    door_once = false;
                    count = 0;
                    break;
                } else count++;
            }

            if (search[count] == buffer[n] && door_once == false) {
                door_once = true; count++;
            }

        }

        if (count == strlen(search)) printf("------------\nSmaug found the Arkenstone!\n\n%s\n------------", buffer);
        else if (count < strlen(search) && count > 4) printf("\n\nSmaug found a gem, mhm.. \n\n%s\n\n", buffer);

    }

    ras_closefile();

    return;
}
