cmake_minimum_required(VERSION 3.17)
project(testTask)

set(CMAKE_CXX_STANDARD 14)

add_executable(testTask main.cpp iTape.h Tape.cpp Tape.h MyTape.cpp MyTape.h sort.cpp sort.h)