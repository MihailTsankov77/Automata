cmake_minimum_required(VERSION 3.24)
project(Automata)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Automata main.cpp
        BaseComponents/Pair/MyPair.hpp
        BaseComponents/Vector/MyVector.hpp Main/State.h Main/State.cpp Main/Automata.h Main/Automata.cpp BaseComponents/Set/MySet.hpp
        BaseComponents/Ptrs/MySharePtr.hpp BaseComponents/Ptrs/MyWeakPtr.hpp Factory/AutomataInterface.h Factory/AutomataInterface.cpp Factory/Files/FileManager.h Factory/Files/FileManager.cpp Factory/Parsers/RegExParser.h Factory/Parsers/RegExParser.cpp BaseComponents/String/MyString.h BaseComponents/String/MyString.cpp)
