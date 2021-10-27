#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "rsd.h"

DIR* rsd_directory[255];
struct dirent* rsd_struct;
struct stat rsd_stat;
int rsd_pos = 0;
char rsd_cwdir[255];
char rsd_wdirbak[255];

void rsd_dirpath(char *cwdir, char *dir, char *result) {
    sprintf(result, "%s\\%s", cwdir, dir);
    return;
}

int rsd_gobackdir(char *src) {

    int length = strlen(src);
    for (int n = length; n > 0; n--) {
        if (src[n] == '\\') {
            src[n] = '\0';
            break;
        }
    }

    if (strcmp(rsd_cwdir, rsd_wdirbak) == 0) return -1;

    return 0;
}

int rsd_lastopen(void) {

    // returns last avaiable DIR* to write into
    // if exceeds the limit, it starts from -1 to report full dir struct
    int end = 0;
    for (int n = 0; n < 255; n++) {
        if (rsd_directory[n] == NULL) { end = n; break; }
        if (n >= 254) { end = -1; break; }
    }

    return end;
}

int rsd_close(void) {

    // return last open position to close
    rsd_pos = rsd_lastopen();

    printf("\n\n %d  dir: %s\n", rsd_pos, rsd_cwdir);

    // if rsd_pos is behind init, reset to zer0
    //rsd_pos -= 1;
    if (rsd_pos <= 0) return -1;

    if (rsd_gobackdir(rsd_cwdir) == -1) return -1;

    if (rsd_directory[rsd_pos] != NULL) { closedir(rsd_directory[rsd_pos]); rsd_directory[rsd_pos] = NULL; }
    rsd_pos -= 1;

    if (rsd_pos <= 0) return -1;
    return 0;
}

void rsd_closeall(void) {

    int end = 0;
    for ( ; end < 255; end++) {
        if (rsd_directory[end] != NULL) { closedir(rsd_directory[end]); }
    }

    return;
}

bool rsd_open(char *dir) {

    rsd_pos = rsd_lastopen();

    rsd_directory[rsd_pos] = opendir(dir);
    if (rsd_directory[rsd_pos] == NULL) { return false; }

    return true;
}

int rsd_read(char *result) {

    rsd_struct = readdir(rsd_directory[rsd_pos]);
    if (rsd_struct == NULL) return -1;

    char buffer[255];
    sprintf(buffer, "%s\\%s", rsd_cwdir, rsd_struct->d_name);

    if (stat(buffer, &rsd_stat) != 0) perror("error stat: ");

    strcpy(result, buffer);

    if (S_ISDIR(rsd_stat.st_mode) == true) return 0;
    else return 1;
}
