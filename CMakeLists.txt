cmake_minimum_required(VERSION 3.10)

project(MarchingCubes)

add_library(glad STATIC deps/glad/src/glad.c)
target_include_directories(glad PUBLIC deps/glad/include)

add_subdirectory(deps/glfw)

set(SHADERS_SRC "${CMAKE_SOURCE_DIR}/shaders")
set(SHADERS_DST "${CMAKE_BINARY_DIR}/shaders")

# Copy shaders every build
add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${SHADERS_SRC}" "${SHADERS_DST}"
    COMMENT "Copying shaders..."
)

find_package(OpenGL REQUIRED)

file(GLOB SOURCES "src/*.cpp")
add_executable(MarchingCubes ${SOURCES} "src/main.cpp")

target_include_directories(MarchingCubes PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(MarchingCubes PRIVATE glad glfw OpenGL::GL)
