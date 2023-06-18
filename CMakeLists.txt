cmake_minimum_required(VERSION 3.24)
project(Automata)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Automata main.cpp
        BaseComponents/MyPair.hpp
        BaseComponents/MyVector.hpp State.h State.cpp  Automata.h Automata.cpp BaseComponents/MySet.hpp
        BaseComponents/MySharePtr.hpp BaseComponents/MyWeakPtr.hpp)
