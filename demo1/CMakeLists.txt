# 指定 CMake 使用版本
cmake_minimum_required(VERSION 3.6)
# 工程名
project(hello)
#设置变量
set(SRC_LIST hello.cpp)
# 编译可执行文件
add_executable(helloBin ${SRC_LIST} )