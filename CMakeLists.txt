cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_REQUIRED ON)

project(raycast-engine)

file(GLOB_RECURSE SRC_FILES src/*.c*)

find_package(SDL2 REQUIRED)

add_executable(raycast-engine ${SRC_FILES})
target_include_directories(raycast-engine
 PUBLIC
 ${CMAKE_CURRENT_SOURCE_DIR}/src
 ${SDL2_INCLUDE_DIRS})

target_link_libraries(raycast-engine
 PUBLIC
 ${SDL2_LIBRARIES}
 pthread)
