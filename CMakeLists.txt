cmake_minimum_required(VERSION 3.0.0)
project(WordleJALADAdmin VERSION 0.1.0)

# source files
file(GLOB_RECURSE SRC_FILES ./src/*.c)
add_executable(WordleJALADAdmin ${SRC_FILES})

# asset files
file(GLOB_RECURSE RESOURCE_FILES ./resources/*.*)
file(COPY ${RESOURCE_FILES} DESTINATION ${CMAKE_BINARY_DIR})

# compile options
target_compile_options(WordleJALADAdmin PRIVATE -Wall)


# CMake options
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})