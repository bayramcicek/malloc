cmake_minimum_required(VERSION 3.16)
project(malloc C)

set(CMAKE_C_STANDARD 11)
set(SOURCE_FILES
        main.c
        malloc_new.c
        malloc_new.h

        )

add_executable(malloc ${SOURCE_FILES})