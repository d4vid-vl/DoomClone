cmake_minimum_required(VERSION 3.20)
project(DoomClone)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB_RECURSE SRC_FILES src/*.c)

add_executable(Doom main.c ${SRC_FILES})
target_link_libraries(Doom ${SDL2_LIBRARIES})
target_include_directories(Doom PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
