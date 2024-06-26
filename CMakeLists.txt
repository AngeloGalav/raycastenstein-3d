cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_REQUIRED ON)

project(raycast-engine)

file(GLOB_RECURSE SRC_FILES src/*.c*)
file(GLOB_RECURSE ASSETS res/*)
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR}/textures)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

option(NO_TEXTURES "Disables textures" OFF)

if(NO_TEXTURES)
    add_definitions(-DUSE_TEXTURES=0)
endif(NO_TEXTURES)

add_executable(raycast-engine ${SRC_FILES})
target_include_directories(raycast-engine
 PUBLIC
 ${CMAKE_CURRENT_SOURCE_DIR}/src
 ${SDL2_INCLUDE_DIRS})

target_link_libraries(raycast-engine
 PUBLIC
 SDL2_image
 ${SDL2_LIBRARIES}
 pthread)
