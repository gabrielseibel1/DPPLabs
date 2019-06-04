cmake_minimum_required(VERSION 3.13)
project(ap2)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()

include_directories(.)
include_directories(src)

add_executable(pi
        src/pi.c)

add_executable(mm
        src/mm.c)