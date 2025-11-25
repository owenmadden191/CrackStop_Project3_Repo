cmake_minimum_required(VERSION 3.10)
project(Project3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project3 main.cpp
        List.cpp
        List.h
        hashclass.cpp
        hashclass.h
        bloomfilterClass.h
        bloomfilterClass.cpp)
