cmake_minimum_required(VERSION 3.0.0)

# projects
project(WordleJALADAdmin VERSION 0.1.0)
project(WordleJALADCliente VERSION 0.1.0)
project(WordleJALADServer VERSION 0.1.0)

# source files
file(GLOB_RECURSE COMMON ./src/common/*.c ./src/common/*.cpp)
file(GLOB_RECURSE DATOS ./src/datos/*.c ./src/datos/*.cpp)
file(GLOB_RECURSE MENU ./src/menu/*.c ./src/menu/*.cpp)
file(GLOB_RECURSE SOCKETS ./src/sockets/*.c ./src/sockets/*.cpp)
file(GLOB_RECURSE ADMIN ./src/admin/*.c)
file(GLOB_RECURSE CLIENTE ./src/cliente/*.c ./src/cliente/*.cpp)
file(GLOB_RECURSE SERVER ./src/server/*.c ./src/server/*.cpp)

# executables
add_executable(WordleJALADAdmin ${ADMIN} ${DATOS} ${COMMON} ${MENU})
add_executable(WordleJALADCliente ${CLIENTE} ${COMMON} ${MENU} ${SOCKETS})
add_executable(WordleJALADServer ${SERVER} ${DATOS} ${COMMON} ${MENU} ${SOCKETS})

# asset files
#file(GLOB_RECURSE RESOURCE_FILES ./resources/*.*)
#file(COPY ${RESOURCE_FILES} DESTINATION ${CMAKE_BINARY_DIR})

# compile options
target_compile_options(WordleJALADAdmin PRIVATE -Wall)
target_compile_options(WordleJALADCliente PRIVATE -Wall)
target_compile_options(WordleJALADServer PRIVATE -Wall)

# libs
# sqlite3
add_subdirectory(libs/sqlite3 EXCLUDE_FROM_ALL)
target_link_libraries(WordleJALADAdmin PRIVATE sqlite3)
target_link_libraries(WordleJALADServer PRIVATE sqlite3)

# openssl crypto
add_subdirectory(libs/openssl EXCLUDE_FROM_ALL)
target_link_libraries(WordleJALADAdmin PRIVATE crypto)
target_link_libraries(WordleJALADServer PRIVATE crypto)

# winsock2 for windows only
if(WIN32)
  target_link_libraries(WordleJALADServer wsock32 ws2_32)
  target_link_libraries(WordleJALADClient wsock32 ws2_32)
endif()