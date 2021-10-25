#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>

#include "rsd.h"
#include "ras.h"

FILE *ras_fd = NULL;

void ras_checkargv(void) {
    // future update
    return;
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

        if (count == strlen(text)) printf("\n\nFOUND SOMETHING!!!!!!!!!!!!!\n\n%s\n\n", buffer);
        else if (count < strlen(text) && count > 4) printf("\n\nFound something, mumble mumble... \n\n%s\n\n", buffer);

    }

    if (count == 0) printf("Not found the cat, searching still.. /%s                           \r", rsd_struct->d_name);
    else if (count > 4) printf("Found something, look below! Searching still.. /%s\n", rsd_struct->d_name);

    ras_closefile();

    return;
}
