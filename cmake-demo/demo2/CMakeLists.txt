# 指定 CMake 使用版本
cmake_minimum_required(VERSION 3.6)

# 项目信息
project (demo2)

# 查找目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(mainBin ${DIR_SRCS})
