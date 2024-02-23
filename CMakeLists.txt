cmake_minimum_required(VERSION 3.27)
project(CeasarCrypt)

set(CMAKE_CXX_STANDARD 17)

add_executable(CeasarCrypt main.c
        convert.h
        convert.c
        random.h
        random.c)
