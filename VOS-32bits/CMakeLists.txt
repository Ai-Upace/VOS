cmake_minimum_required(VERSION 3.12)
project(VOS C ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/drivers
        ${PROJECT_SOURCE_DIR}/include/user
        ${PROJECT_SOURCE_DIR}/libc
)

# 递归查找所有C和ASM源文件
file(GLOB_RECURSE VOS_SOURCES
        ${PROJECT_SOURCE_DIR}/src/*.c
        ${PROJECT_SOURCE_DIR}/src/*.asm
        ${PROJECT_SOURCE_DIR}/src/*.s
        ${PROJECT_SOURCE_DIR}/std/*.c
)

add_executable(vos ${VOS_SOURCES})

# 可选：编译选项
add_compile_options(-ffreestanding -Wall -nostdlib -Wextra -Werror)

# 可选：设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)