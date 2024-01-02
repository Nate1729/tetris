add_library(glad "")

target_sources(glad
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/glad.c
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/khrplatform.h
    ${CMAKE_CURRENT_LIST_DIR}/glad.h
)

target_include_directories(glad
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)
