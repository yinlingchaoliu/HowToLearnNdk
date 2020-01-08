# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.6)

# 项目信息
project (demo6)

# 检查系统是否支持 pow 函数
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
check_function_exists (pow HAVE_POW)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# 是否加入 cmath 库
if (NOT HAVE_POW)
  include_directories ("${PROJECT_SOURCE_DIR}/cmath")
  add_subdirectory (cmath)
  set (EXTRA_LIBS ${EXTRA_LIBS} cmath)
endif (NOT HAVE_POW)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

set (MAIN_BIN mainBin)

# 指定生成目标
add_executable(${MAIN_BIN} ${DIR_SRCS})
target_link_libraries (${MAIN_BIN}  ${EXTRA_LIBS})