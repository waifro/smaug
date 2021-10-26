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

int ras_checkargv(int argc, char **argv, char *result) {

    if (argc < 2) {
        printf("no command found, use '-h' or '--help' next time.\n");
        return -1;
    }

    char commands[9][10] = {"-e", "--head", "-t", "--tail", "-l", "--length", "-h", "--help" };

    for (int n = 1; n <= argc; n++) {

        printf("head: %s\ntail: %s\nlength: %d\n", ras_head, ras_tail, ras_len);

        for (int i = 0; i < 9; i++) {

            if (strcmp(commands[i], argv[n]) == 0) {

                if (i == 0 || i == 1) {
                    strcpy(ras_head, argv[n+1]);
                } else if (i == 2 || i == 3) {
                    strcpy(ras_tail, argv[n+1]);
                } else if (i == 4 || i == 5) {
                    ras_len = atoi(argv[n+1]);
                } else if (i == 6 || i == 7) {
                    printf("[%s] >> see readme on github\n", argv[n]);
                    return -1;
                }
            }
        }
    }

    for (int n = 0; n <= ras_len; n++) {
        if (n == 0) { strcpy(result, ras_head); n += strlen(ras_head); }
        else if (n != ras_len) result[n] = '#';
        if (n == ras_len) {strcpy(&result[n], ras_tail); break; }
    }

    printf("head: %s\ntail: %s\nlength: %d\nresult %s\n", ras_head, ras_tail, ras_len, result);

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

void ras_findargv(char *file, char *text) {

    if (ras_openfile(file) != 0) return;

    char buffer[255];
    int length_buf; int count = 0;
    bool door_once = false;

    while(1) {

        if (fgets(buffer, 255, ras_fd) == NULL) break;

        length_buf = strlen(buffer) - 1;
        for (int n = 0; n < length_buf; n++) {

            if(door_once == true) {
                if (text[count] != buffer[n]) {
                    door_once = false;
                    count = 0;
                    break;
                } else count++;
            }

            if (text[count] == buffer[n] && door_once == false) {
                door_once = true; count++;
            }

        }

        if (count == strlen(text)) printf("\n\nSmaug found the Arkenstone!\n\n%s\n\n", buffer);
        else if (count < strlen(text) && count > 4) printf("\n\nSmaug found something, mumble mumble... \n\n%s\n\n", buffer);

    }

    if (count == 0) printf("searching for the Arkenstone, searching still.. /%s                           \r", rsd_struct->d_name);
    else if (count > 4) printf("Found something, look below! Searching still.. /%s\n", rsd_struct->d_name);

    ras_closefile();

    return;
}
