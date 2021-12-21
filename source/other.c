
#ifdef _WIN32
    #include "mman.h" // mman-win32
#else 
    #include <sys/mman.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "other.h"


char *strcpy_cinj(char *src, int index, char *ptr) {
    /* inject a string inside another string, specify starting index */

    char *s1 = malloc(sizeof(char) * (strlen(ptr) + strlen(src) + 2) );
    if (!s1) return NULL;

    char *s2 = src + index; char *s1_pt = s1;

    *s1 = *s2;
    for (int n = 0; *s2 != '\0'; n++) *s1++ = *s2++;

    s2 = src + index; s1 = s1_pt;

    for (int n = 0; *s1 != '\0'; n++)
        if (*ptr == '\0') *s2++ = *s1++;
        else *s2++ = *ptr++;

    return (src);
}

int strlen_ctok(const char *ptr, char tok) {
  if (ptr == NULL) return -1;

  for (int n = 0; ; n++) {
    if (n == 0 && ptr[n] == '\0') return 0;
    if (ptr[n] == '\0' || ptr[n] == tok) return (n);
  }

  return -1;
}

size_t fdsize(int fd) {
    struct stat st = {0};
    fstat(fd, &st);
    return (st.st_size);
}

int strcmp_ctok(char *ptr, char tok) {
    for (int n = 0; ; n++) {
        if (ptr[n] == '\0') return -1;
        else if (ptr[n] == tok) return 0;
    }
}

/*
int main() {

    // open file pointer
    FILE *fp = fopen("file.txt", "r+");
    if (fp == NULL) {
        printf("error file");
        return -1;
    }

    char *ptr = "deems_domingo@yahoo.com:ewfdsvcds";

    char buffer[256]; int fp_index = 0;
    while(fgets(buffer, 256, fp) != NULL) {

        // get index length till ':'
        int len = strlen_ctok(buffer, ':');

        if (strncmp(buffer, ptr, len+1) == 0) {

            // convert fp to fd
            int fd = fileno(fp);

            // get size of file
            len = strlen_ctok(ptr, ':') + 1;
            size_t size = fdsize(fd);

            // truncate of length size to the file descriptor
            ftruncate(fd, size + strlen(&ptr[len]));

            // file mapping
            char *map = mmap(NULL, size + strlen(&ptr[len]), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            if (map == NULL) {
                printf("errno: %d", errno);
                return -1;
            }

            int n = (int)fp_index + strlen(buffer);

            char buf[256];
            sprintf(buf, ",%s", &ptr[len]);

            if (strcpy_cinj(map, n-2, buf) == NULL) {
                ftruncate(fd, size);
                return -1;
            }

            // sync & close
            msync(map, sizeof(map), MS_SYNC);
            munmap(map, sizeof(map)); close(fd);

            break;
        }

        // get length of fgets for future injection
        fp_index += strlen(buffer);

    }

    fclose(fp);

    return 0;
}
*/
