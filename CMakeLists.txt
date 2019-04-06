cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11 -Wall -Wextra -lm")
project(tp_res C)

set(CMAKE_C_STANDARD 99)
include_directories(include)
find_library(M_LIB m)
set(
        SHARED
        src/coding.c
        src/decoding.c
        src/error.c
        src/logic.c
        src/sockettoolbox.c
)
add_executable(sending sending.c ${SHARED})
add_executable(receiving receiving.c ${SHARED})
add_executable(medium medium.c ${SHARED})
add_executable(main main.c ${SHARED})
target_link_libraries(sending ${M_LIB})
target_link_libraries(receiving ${M_LIB})
target_link_libraries(medium ${M_LIB})
target_link_libraries(main ${M_LIB})