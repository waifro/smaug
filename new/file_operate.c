#include <stdio.h>
#include <string.h>
#include <stdbool.h>ù

#include "file_operate.h"

// strin: variable for search
int FILE_SearchString(char *strin, char *buffer) {

    int i = strlen(buffer); int j = 0;
    bool check = false; // int count;
    for (int n = 0; n < i; n++) {

        if (check == true) {
            if (strin[j] == '#') { j+= 1; continue; }
            if (strin[j] == buffer[n]) {j+= 1; continue; }
            if (strin[j] != buffer[n]) break;
        }

        if (check == false && strin[j] == buffer[n]) { j+= 1; check = true; }
    }

    if (strlen(strin) == j) return -1;
    else return j;
}
