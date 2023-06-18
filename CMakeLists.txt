cmake_minimum_required(VERSION 3.24)
project(Automata)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Automata
        BaseComponents/MyPair.hpp
        BaseComponents/trash/MyReferenceCounter.cpp
        BaseComponents/trash/MyReferenceCounter.h
        BaseComponents/trash/MySharedPointer.hpp
        BaseComponents/MyVector.hpp State.h State.cpp main.cpp Automata.h BaseComponents/SharePtr.hpp Automata.cpp BaseComponents/MySet.hpp BaseComponents/MyString.h BaseComponents/MyString.cpp)
