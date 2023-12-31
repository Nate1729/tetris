cmake_minimum_required(VERSION 3.27.7)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(tetris C)

add_executable(${PROJECT_NAME} main.c glad.c)

add_subdirectory(external/glfw)


target_include_directories(${PROJECT_NAME}
  PUBLIC external/glfw/include
  PUBLIC include/
)

target_link_directories(${PROJECT_NAME}
  PUBLIC external/glfw/src
)

target_link_libraries(${PROJECT_NAME} glfw)

