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

    printf("\n\n                        Smaug v0.1 (Lord of the Rings)\n            Search inside every file, folder and subfolder for OSINT\n");
    printf("    to carefully look for someone/something or try to find someone/something\n\n");

    if (argv[1] == NULL) { printf("no command found, exit\n"); return 0; }
    else if (argv[2] != NULL) { printf("too many commands, exit\n"); return 0; }


    // get current diectory
    getcwd(rsd_cwdir, 255);
    printf("\ncurrent directory: %s\n\n", rsd_cwdir);

    // open stream directory
    if (rsd_open(rsd_cwdir) == false) return 0;

    char buffer[255]; int res;

    while(1) {
        res = rsd_read(buffer);

        if (res == 0) {

            if (buffer[strlen(buffer)-1] != '.') {

                printf(" dir: %s\n", buffer);

                strcpy(rsd_cwdir, buffer);
                if (rsd_open(rsd_cwdir) == false) return 0;
            }

        }

        else if (res == 1) ras_findargv(buffer, argv[1]);

        else if (res == -1) {

                if (rsd_lastopen() == -1) break;
            else {
                rsd_close();
            }
        }
    }

    rsd_closeall();

    return 0;
}
