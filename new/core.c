#include <stdio.h>

#include "dir_tree.h"
#include "dir_operate.h"

void CORE_Testing(void) {

    char buffer[256];
    DIR_OperativeTree(buffer);

    printf("%s\n", buffer);

    return;
}
