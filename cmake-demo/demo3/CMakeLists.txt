# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.6)

# 项目信息
project (demo3)

# 查找目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加 hello 子目录
add_subdirectory(hello)

# 指定生成目标
add_executable(HelloBin ${DIR_SRCS})

# 添加链接库
target_link_libraries(HelloBin hello)

#先生成二进制目标，再添加链接库