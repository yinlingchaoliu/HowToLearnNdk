cmake_minimum_required (VERSION 3.6)

# 项目信息
project (demo8)
set (Demo_VERSION_MAJOR 1)
set (Demo_VERSION_MINOR 0)

# 检查系统是否支持 pow 函数
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
check_function_exists (pow HAVE_POW)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# 是否加入 MathFunctions 库
if (NOT HAVE_POW)
  include_directories ("${PROJECT_SOURCE_DIR}/cmath")
  add_subdirectory (cmath)
  set (EXTRA_LIBS ${EXTRA_LIBS} cmath)
endif (NOT HAVE_POW)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

set(MAIN_BIN mainBin)

# 指定生成目标
add_executable(${MAIN_BIN} ${DIR_SRCS})
target_link_libraries (${MAIN_BIN}  ${EXTRA_LIBS})

# 指定安装路径
install (TARGETS ${MAIN_BIN} DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)

# 启用测试
enable_testing()

# 测试程序是否成功运行
#语法 add_test(flag , bin ,arg1,arg2...) eg 1:
add_test (test_demo ${MAIN_BIN} 5 2)

# 测试帮助信息是否可以正常提示
add_test (test_usage ${MAIN_BIN})
set_tests_properties (test_usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent")

# 测试 5 的平方 为 25
add_test (test_5_2 ${MAIN_BIN} 5 2)
set_tests_properties (test_5_2 PROPERTIES PASS_REGULAR_EXPRESSION "is 25")

# 定义一个宏，用来简化测试工作  测试函数 抽象工作
macro (do_test arg1 arg2 result)
  add_test (do_test_${arg1}_${arg2} ${MAIN_BIN} ${arg1} ${arg2})
  set_tests_properties (do_test_${arg1}_${arg2} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

# 利用 do_test 宏，测试一系列数据,起到简化效果
do_test (2 10 "is 1024")
do_test (3 3 "is 27")
do_test (8 2 "is 64")

# 构建一个 CPack 安装包
include (InstallRequiredSystemLibraries)
# License授权
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Demo_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Demo_VERSION_MINOR}")
include (CPack)
