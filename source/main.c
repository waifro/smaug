#include <stdio.h>

#include "core.h"
#include "argv_global.h"

char argv_strin[256];
char *argv_argv[256] = { "-h", "--help" };
char *argv_comment[256] = { "\nno argv, use '-h' next time.\n", "\ninvalid command\n", "\nusage: smaug <argv_to_search>\n- ex. \"/~: smaug helloworld\"\n\nif you have problems not founding argv, use '#' to ignore.\n- ex. \"/~: smaug hel######d\"\n" };

#ifdef _WIN32
    char *glo_charfolder = "\\";
#else
    char *glo_charfolder = "/";
#endif

int main (int argc, char *argv[]) {
    (void)argc; (void)argv;

    CORE_StartSequence(argc, argv);

    return 0;
}
