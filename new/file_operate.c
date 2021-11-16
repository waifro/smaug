#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "file_operate.h"

// strin: variable to match
int FILE_SearchString(char *strin, char *buffer) {

    int i = strlen(buffer); int j = 0;
    bool check = false;
    for (int n = 0; n < i; n++) {

        if (check == true) {
            if (strin[j] == '#') { j+= 1; continue; }
            if (strin[j] == buffer[n]) {j+= 1; continue; }
            if (strin[j] != buffer[n]) break;
        }

        if (check == false && strin[j] == buffer[n]) { j+= 1; check = true; }
    }

    // returns -1 if matches perfectly
    if (strlen(strin) == j) return -1;

    // returns greater then 0 if successful
    // returns 0 if no match
    else return j;
}
