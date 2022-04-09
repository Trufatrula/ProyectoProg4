cmake_minimum_required(VERSION 3.0.0)
project(sqlite3 VERSION 0.1.0)

# source files
add_library(sqlite3 sqlite3.c)
target_include_directories(sqlite3 PUBLIC ./)

# compile options
target_compile_options(WordleJALADAdmin PRIVATE -Wall)

# CMake options
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})   