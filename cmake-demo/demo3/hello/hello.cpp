//
// Created by 陈桐 on 2020/1/7.
//
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

char * sayHello(){
    char * words = (char *)malloc(100*sizeof(char));
    memset(words,0,100);
    strcpy(words,"支持子目录调用");
    return words;
}