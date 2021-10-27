#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "rsd.h"
#include "ras.h"

int main (int argc, char *argv[]) {
    printf("\n\n");
    printf("                              ...',;;:cccccccc:;,..\n");
    printf("                          ..,;:cccc::::ccccclloooolc;'.\n");
    printf("                       .',;:::;;;;:loodxk0kkxxkxxdocccc;;'..\n");
    printf("                     .,;;;,,;:coxldKNWWWMMMMWNNWWNNKkdolcccc:,.\n");
    printf("                  .',;;,',;lxo:...dXWMMMMMMMMNkloOXNNNX0koc:coo;.\n");
    printf("               ..,;:;,,,:ldl'   .kWMMMWXXNWMMMMXd..':d0XWWN0d:;lkd,\n");
    printf("             ..,;;,,'':loc.     lKMMMNl. .c0KNWNK:  ..';lx00X0l,cxo,.\n");
    printf("           ..''....'cooc.       c0NMMX;   .l0XWN0;       ,ddx00occl:.\n");
    printf("         ..'..  .':odc.         .x0KKKkolcld000xc.       .cxxxkkdl:,..\n");
    printf("       ..''..   ;dxolc;'         .lxx000kkxx00kc.      .;looolllol:'..\n");
    printf("       ..'..   .':lloolc:,..       'lxkkkkk0kd,   ..':clc:::;,,;:;,'..\n");
    printf("       ......  ....',;;;:ccc::;;,''',:loddol:,,;:clllolc:;;,'........\n");
    printf("           .    ....'''',,,;;:cccccclllloooollllccc:c:::;,'..\n");
    printf("                  .......'',,,,,,,,;;::::ccccc::::;;;,,''...\n");
    printf("                    ...............''',,,;;;,,''''''......\n");
    printf("                         ............................\n");

    printf("\n\n                            Smaug v0.1 (The Hobbit)\n            Search inside every file, folder and subfolder for OSINT\n");
    printf("    to carefully look for someone/something or try to find someone/something\n\n");

    (void)argc; (void)argv;

    char search[255];
    if (ras_checkargv(argc, argv, search) != 0) return 0;
    printf("\nSmaug is searching for [%s]\n", search);

    // get current directory
    getcwd(rsd_cwdir, 255);
    printf("current directory: %s\n\n", rsd_cwdir);
    // open stream directory
    if (rsd_open(rsd_cwdir) == false) return 0;

    char buffer[255]; int res;


    char wheel[] = "|/-\\";
    int wheel_n = 0;

    while(1) {
        res = rsd_read(buffer);

        if (res == 0) {

            if (buffer[strlen(buffer)-1] != '.') {

                printf("\rdir: %s\n", buffer);

                strcpy(rsd_cwdir, buffer);
                if (rsd_open(rsd_cwdir) == false) return 0;
            }

        }

        else if (res == 1) ras_findargv(buffer, search);

        else if (res == -1) {
            if (rsd_lastopen() == -1) break;
            else  rsd_close();
        }

        if (wheel[wheel_n] == '\0') wheel_n = 0;
        printf("Smaug is searching..%c\r", wheel[wheel_n]);
        wheel_n++;
    }

    rsd_closeall();

    return 0;
}
