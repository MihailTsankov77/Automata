cmake_minimum_required(VERSION 3.24)
project(Automata)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Automata
        MyPair.hpp
        MyReferenceCounter.cpp
        MyReferenceCounter.h
        MySharedPointer.hpp
        MyVector.hpp)
