cmake_minimum_required(VERSION 3.10)
project(serpinski)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb3 -pg")

find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0
add_subdirectory(lib/flecs)
add_subdirectory(lib/imgui)
find_package(Catch2 3 REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
set(HEADERS
  include/
  lib/Unity-2.5.2/src/
)
file(GLOB_RECURSE TESTS tests/*.cpp)

add_library(${PROJECT_NAME}_o ${SOURCES})


# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# Without testing framework
target_link_libraries(${PROJECT_NAME}_o raylib flecs::flecs_static ImGui::imgui)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_o)

# With Testing framework
add_executable(${PROJECT_NAME}_test ${TESTS})
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_o Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME}_test)