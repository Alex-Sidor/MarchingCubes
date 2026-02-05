cmake_minimum_required(VERSION 3.10)

project(MarchingCubes)

add_library(glad STATIC deps/glad/src/glad.c)
target_include_directories(glad PUBLIC deps/glad/include)

add_subdirectory(deps/glfw)
add_subdirectory(deps/glm)

find_package(OpenGL REQUIRED)

file(GLOB SOURCES "src/*.cpp")
add_executable(MarchingCubes ${SOURCES})

target_include_directories(MarchingCubes PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(MarchingCubes PRIVATE glad glfw glm OpenGL::GL)

add_custom_command(
    TARGET MarchingCubes POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:MarchingCubes>/shaders"
)

add_custom_command(
    TARGET MarchingCubes POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:MarchingCubes>/assets"
)