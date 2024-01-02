cmake_minimum_required(VERSION 3.27.7)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY out/build/)

project(tetris C)

add_subdirectory(external/glfw)
add_subdirectory(src)


target_include_directories(${PROJECT_NAME}
  PUBLIC external/glfw/include
  PUBLIC include/
)

target_link_directories(${PROJECT_NAME}
  PUBLIC external/glfw/src
)

target_link_libraries(${PROJECT_NAME} glfw)

