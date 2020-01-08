//
// Created by 陈桐 on 2020/1/7.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
//动态控制代码是否添加
#include "config.h"

#ifdef USE_HELLO
  #include "hello/hello.h"
#endif

void printWorker(){
    printf("扫地僧路过!!!\n");
}

int main(int argc, char *argv[])
{

#ifdef USE_HELLO
        char * words = sayHello();
        printf("%s\n", words);
        free(words);
        words = NULL;
#else
    printWorker();
#endif

    return 0;
}