#pragma once

#include "BaseComponents/MyVector.hpp"
#include "BaseComponents/MyPair.hpp"
#include "BaseComponents/MySharedPointer.hpp"
//TODO: switch
#include <string>

enum StateStatus {
    final = 1,
    begging = 2
};

class State {
private:
    typedef MySharedPointer<State> StatePtr;
    typedef MyPair<int, StatePtr> Id;
    typedef MyVector<StatePtr> Steps;
    typedef MyPair<char, Steps> Connection;
    typedef MyVector<Connection> Connections;

    Id id;
    Connections connections;

public:
    //TODO: move??

    explicit State(int);

    State(int, Connections &);

    State(int, Connections &, char);

private:
    void setId(int);

public:

    bool contains(std::string) const;

    ~State();

private:
    char status = 0;

    void makeStatus(StateStatus);

    void makeNotStatus(StateStatus);

    bool isStatus(StateStatus) const;

public:
    void makeBegging();

    void makeNotBegging();

    bool isBegging() const;

    void makeFinal();

    void makeNotFinal();

    bool isFinal() const;
};

