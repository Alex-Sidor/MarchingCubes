cmake_minimum_required(VERSION 3.10)

project(MarchingCubes)

add_library(glad STATIC deps/glad/src/glad.c)
target_include_directories(glad PUBLIC deps/glad/include)

add_subdirectory(deps/glfw)

find_package(OpenGL REQUIRED)

file(GLOB SOURCES "src/*.cpp")
add_executable(MarchingCubes ${SOURCES} "src/main.cpp")

target_include_directories(MarchingCubes PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(MarchingCubes PRIVATE glad glfw OpenGL::GL)
