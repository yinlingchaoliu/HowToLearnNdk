# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.6)

# 项目信息
project (demo4)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# 自定义编译
# cmake -DUSE_HELLO=OFF CMakeLists.txt  用命令来调节
# 是否使用自己的 hello 库  --option开关选项
option (USE_HELLO "Use provided hello implementation" ON)

# 是否加入 hello 库
if (USE_HELLO)
  include_directories ("${PROJECT_SOURCE_DIR}/hello")
  add_subdirectory (hello)
  set (HELLO_LIBS hello)
endif (USE_HELLO)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable (mainBin ${DIR_SRCS})
target_link_libraries (mainBin  ${HELLO_LIBS})

