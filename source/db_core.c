#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>

#include "db_core.h"
#include "db_dir.h"
#include "db_file.h"
#include "other.h"

#ifdef _WIN32
    #include <direct.h>
    #include "mman.h"
#else 
    #include <sys/mman.h>
#endif

// globals
DIR *dbcore_dir;
char dbcore_startf[512];

// temporary
char dirpath[512];

int DBCORE_SliceData(char *src) {
    for (int n = 0; n <= strlen(src); n++) if (src[n] == ':') return n;
    return -1;
}

// compares the first parameter if matches, sanitizes ptr
int DBCORE_CompareParameterString(char *ptr, char *foo) {

    int n1;
    for (n1 = 0; *ptr != '\0'; n1++) {
        if (*ptr == *foo)  {
            if (*ptr != ':') {
                if (*ptr != ';') {
                    (void)*ptr++; (void)*foo++;
                } else break;
            } else break;
        } else break;
    }

    if (*ptr == *foo) return n1;
    else return -1;
}

int DBCORE_CompareMultipleParam(char *ptr, int index_start, char *foo) {

    bool check = false;

    // n1 for index moving on ptr
    int n1 = index_start;
    // n2 to keep track of index starting at check true at foo
    int n2 = 0;

    (void)n2;
    for (int n = index_start; ; n++) {
        if (ptr[n1] == '\0' || foo[n] == '\0') break;

        if (check == true) {

            if (foo[n] == ptr[n1]) { n1 += 1; continue; }

            if (foo[n] != '\n' && foo[n] != ':' && foo[n] != ';') {
                check = false; n1 = index_start; // reset integers as check till next string equals again
            } else return (n1);

        }

        if (ptr[n1] == foo[n]) {
            check = true; n1 += 1; n2 = n;
        }

    }

    return -1;
}

int DBCORE_SanitizeString(char *ptr, short int index) {

    int ptr_len = strlen(ptr) - 1;
    char *foo = ptr;
    printf("\n\t# warning: multiple strings, sanitizing ptr...");
    printf("\n\t# before: %d, %s", ptr_len, foo);

    for (int n = 0; n < index; n++) {
        (void)*foo++;
    }

    int res1 = strcmp_ctok((char*)ptr, ':');
    if (res1 == -1) {

        if ((res1 = strcmp_ctok((char*)ptr, ';')) == -1) {
            printf("\n\t# error: string not valid\n");
            return -1;
        }
    }

    ptr_len = strlen(foo);
    strcpy(ptr, foo);

    printf("\t#  after: %d, %s\n", ptr_len, ptr);
    return (ptr_len);
}

int DBCORE_CheckStringStatus(char *ptr) {
    int check = 0;
    for (int n = 0; ptr[n] != '\0'; n++) {
        if (ptr[n] == '@') check++;
    }

    if (check != 0) return (check);
    else return 0;
}

int DBCORE_StartSequence(char *ptr) {

    // check if db-sort folder exist
    if (DBDIR_CheckFolder(dbcore_startf) != 0) {
        mkdir(dbcore_startf, 0777);
    }

    int ptr_len = strlen(ptr) - 1;

    char file_cwbuffer[1024];
    int count = 1;

    bool check = false;

    // after this while loop, you should get the filename
    while(1) {

        if (check == true) break;

        // check & create folfer alphabetic
        char cwbuffer[512];
        if (DBDIR_CheckAlphaStructure((char*)ptr, cwbuffer) != 0) {
            printf("\t# error: DBCORE_CheckAlphaStructure()\n");
            return -1;
        }

        sprintf(file_cwbuffer, "%s\\%d.txt", cwbuffer, count);

        DBFILE_CheckFile(file_cwbuffer);
        FILE *fp = fopen(file_cwbuffer, "r+");

        char fp_buffer[512];
        int fp_index = 0; int res1 = 0;

        int count_line = 0;

        while(1) {

            char *result = fgets(fp_buffer, 512, fp);

            // empty file
            if (result == NULL) {

                if (count_line >= 10001) {
                    count++;
                    break;
                }

                fprintf(fp, "%s", ptr);
                check = true; break;
            }

            fp_index += (int)strlen(fp_buffer) + 1;
            count_line++;

            // string might be the same as a previous written string
            if ((res1 = DBCORE_CompareParameterString(ptr, fp_buffer)) != -1) {

                // compare passwords
                if ((res1 = DBCORE_CompareMultipleParam(ptr, res1 + 1, fp_buffer)) != -1) {

                    // if password matches, use length of password + res1 to index for sanitize
                    if (DBCORE_CheckStringStatus(ptr) > 1) {

                        if (DBCORE_SanitizeString(ptr, res1) != -1) {
                            printf("\t# warning: new string not expected, restarting...\n\n");
                            count = 1; break;
                        }
                    }

                    else {
                        printf("\t>> parameters already exists, done.\n");
                        check = true;
                        break;
                    }
                }
            }

            // should we check for used passwords? ngl, im not sure, but its okay as of right now
            if (strncmp(fp_buffer, ptr, strlen_ctok(fp_buffer, ':') + 1) == 0) {

                // first, we prepare a buffer for later usage
                int ptr_tok = strlen_ctok(ptr, ':') + 1;

                char buffer[512];

                int i = 0; buffer[i] = ';'; i++;
                for (int n = ptr_tok; n < ptr_len; n++) {
                    if (i >= 511) {
                        printf("\t# error: string too big to copy\n");
                        return -2;
                    }

                    buffer[i] = ptr[n]; i++;
                }

                buffer[i] = '\0';

                int fd = fileno(fp);
                int fd_size = fdsize(fd);

                // gets the length of buffer - null terminator
                int buff_len = (int)strlen(buffer);

                // truncates more of ptr_tok to the file descriptor
                ftruncate(fd, fd_size + buff_len);

                // file mapping
                char *map = mmap(NULL, fd_size + buff_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
                if (map == NULL) {
                    printf("\t# error mmap: %d\n", errno);
                    ftruncate(fd, fd_size); return -1;
                }

                if (strcpy_cinj(map, fp_index - 2, buffer) == NULL) {
                    printf("\t# error malloc: %d\n", errno);
                    ftruncate(fd, fd_size); return -1;
                }

                // sync & close
                msync(map, sizeof(map), MS_SYNC);
                munmap(map, sizeof(map)); close(fd);
                check = true; break;
            }

        }

        fclose(fp);
    }

    // file zone

    // goto root directory - done
    // check if folder exists - done
    // create folder - done
    // check if file exists - done
    // create file - done
    // scan file if theres more accounts - done
    // check if account already exists - done
    // check if equal psws - done
    // write if not, ignore if equal - done
    // write at the end or near account breached - done
    // close file - done
    // close folder - done

    return 0;
}
