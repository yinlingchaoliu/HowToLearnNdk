# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.6)

# 项目信息
project (demo7)

# 设置项目版本号
set (Demo_VERSION_MAJOR 1)
set (Demo_VERSION_MINOR 0)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

set (MAIN_BIN mainBin)

# 指定生成目标
add_executable(${MAIN_BIN} ${DIR_SRCS})