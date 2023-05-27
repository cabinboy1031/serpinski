cmake_minimum_required(VERSION 3.10)
project(serpinski)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb3 -pg")

find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0
find_package(flecs REQUIRED)


file(GLOB_RECURSE SOURCES src/*.c)
set(HEADERS
  include/
  lib/Unity-2.5.2/src/
)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} raylib flecs::flecs_static)


# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()