cmake_minimum_required(VERSION 3.14)
project(Tmp)

set(CMAKE_CXX_STANDARD 11)


FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()


# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
# 添加 src 子目录
add_subdirectory(src)
# 指定生成目标
add_executable(Tmp main.cpp)
# 添加链接库
target_link_libraries(Tmp MathFunctions)