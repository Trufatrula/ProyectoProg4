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

# libs
# sqlite3
add_subdirectory(libs/sqlite3 EXCLUDE_FROM_ALL)
target_link_libraries(WordleJALADAdmin PRIVATE sqlite3)

# openssl crypto
add_subdirectory(libs/openssl EXCLUDE_FROM_ALL)
target_link_libraries(WordleJALADAdmin PRIVATE crypto)

# CMake options
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})