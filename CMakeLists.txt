cmake_minimum_required(VERSION 3.10)
project(chess_project)

# 使用 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找编译器信息
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ version: ${CMAKE_CXX_COMPILER_VERSION}")

# 添加可执行文件
add_executable(chess_game 
    src/main.cpp 
    src/chess.cpp 
    src/FileIO.cpp
    src/ai.cpp
)

# 包含头文件目录
target_include_directories(chess_game PRIVATE include)

# Ubuntu 上链接文件系统库的完整方法
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC 8 及以上版本需要链接 stdc++fs
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8.0)
        target_link_libraries(chess_game stdc++fs)
        message(STATUS "Linking stdc++fs for GCC ${CMAKE_CXX_COMPILER_VERSION}")
    else()
        message(STATUS "GCC version ${CMAKE_CXX_COMPILER_VERSION} may not need stdc++fs")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Clang 通常不需要特别链接
    message(STATUS "Clang compiler detected, no special linking needed")
endif()