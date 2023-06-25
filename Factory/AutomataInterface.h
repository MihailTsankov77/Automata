#pragma once
#include "../BaseComponents/Vector/MyVector.hpp"
#include "../Main/Automata.h"

enum Commands{
    accepts = 0,
    createFromText,
    saveInFile,
    createFromRegEx,
    getRegEx,
    concat,
    onion,
    kleeneStar,
    determine,
    minimize,
    reverse,
    print,
    total,
    info,
    terminate
};

class AutomataInterface
{
    MyVector<Automata> automates;

    AutomataInterface() = default;
    AutomataInterface(const AutomataInterface&) = delete;
    AutomataInterface& operator=(const AutomataInterface&) = delete;

    void oneItemCommand(int);
    void twoItemCommand(int);
    void printInfo();
public:
    static AutomataInterface & getInstance();

    bool readCommand();
};