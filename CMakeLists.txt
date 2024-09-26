CMAKE_MINIMUM_REQUIRED(VERSION 3.12) # cmake最低版本要求

PROJECT(shudu)    # 工程名 CppTemplate

set(CMAKE_CXX_STANDARD 11) # C++17标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_subdirectory(test) # 添加test子目录

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin") # 可执行文件输出目录

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include") # 头文件包含目录


MESSAGE("This is Windows.")
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options("/source-charset:utf-8")
    add_compile_options("/execution-charset:utf-8")
else()
    add_compile_options("-finput-charset=utf-8")
    add_compile_options("-fexec-charset=utf-8")
endif()

AUX_SOURCE_DIRECTORY(src DIR_SRCS) # 添加源代码文件夹, 自动扫描所有文件

add_executable(shudu  # 输出名为sudoku的可执行文件
   ${DIR_SRCS}
)
