cmake_minimum_required(VERSION 3.27)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(imageprocessor main.c
        io.c
        io.h
        process.c
        process.h)
