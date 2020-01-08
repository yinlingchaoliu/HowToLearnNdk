//
// Created by 陈桐 on 2020/1/7.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "hello/hello.h"

int main(int argc, char *argv[])
{
    char * words = sayHello();
    printf("%s\n", words);
    free(words);
    words = NULL;
    return 0;
}
