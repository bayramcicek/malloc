cmake_minimum_required(VERSION 3.16)
project(malloc C)

set(CMAKE_C_STANDARD 11)
set(SOURCE_FILES
        main.c
        new_malloc.c
        new_malloc.h

        )

add_executable(malloc ${SOURCE_FILES})