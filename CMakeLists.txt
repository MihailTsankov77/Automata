cmake_minimum_required(VERSION 3.24)
project(Automata)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Automata
        BaseComponents/MyPair.hpp
        BaseComponents/MyReferenceCounter.cpp
        BaseComponents/MyReferenceCounter.h
        BaseComponents/MySharedPointer.hpp
        BaseComponents/MyVector.hpp State.h State.cpp main.cpp)
