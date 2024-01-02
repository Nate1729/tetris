cmake_minimum_required(VERSION 3.27.7)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(tetris C)

add_executable(${PROJECT_NAME} src/main.c)


add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(src)


target_include_directories(${PROJECT_NAME}
  PUBLIC external/glfw/include
  PUBLIC external/glad/include
  PUBLIC include/
)

target_link_directories(${PROJECT_NAME}
  PUBLIC external/glfw/src
  PUBLIC external/glad
)

target_link_libraries(${PROJECT_NAME} glfw glad)

