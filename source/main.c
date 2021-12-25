#include <stdio.h>
#include "core.h"
#include "other.h"

#ifdef _WIN32
    char *CONSOLE_RED = "";
    char *CONSOLE_GREEN = "";
    char *CONSOLE_YELLOW = "";
    char *CONSOLE_RESET = "";

    char *glo_charfolder = "\\";
#else
    char *CONSOLE_RED = "\x1b[0;31m";
    char *CONSOLE_GREEN = "\x1b[0;32m";
    char *CONSOLE_YELLOW = "\x1b[0;33m";
    char *CONSOLE_RESET = "\x1b[0m";

    char *glo_charfolder = "/";
#endif

int main (int argc, char *argv[]) {
    (void)argc; (void)argv;

    CORE_Testing();

    return 0;
}
