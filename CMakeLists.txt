cmake_minimum_required(VERSION 3.20)
project(library_manager C)

set(CMAKE_C_STANDARD 23)

add_executable(library_manager
        main.c
        Book.c
)
