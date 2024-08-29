cmake_minimum_required(VERSION 3.10)
project(MySimpleProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(MySimpleProject main.cpp
        SudokuBoard.cpp
        SudokuBoard.h)
