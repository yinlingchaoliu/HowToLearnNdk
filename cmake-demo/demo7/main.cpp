#include <stdio.h>
#include <stdlib.h>
#include "config.h"

int main(int argc, char *argv[])
{
    printf("%s Version %d.%d\n",
            argv[0],
            Demo_VERSION_MAJOR,
            Demo_VERSION_MINOR);
    return 0;
}
