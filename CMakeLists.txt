cmake_minimum_required(VERSION 3.13)
project(ASG3_EyasRashid)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ASG3_EyasRashid
        graphl.cpp
        graphl.h
        graphm.cpp
        graphm.h
        main.cpp
        nodedata.cpp
        nodedata.h)
