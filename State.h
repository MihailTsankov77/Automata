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
public:
    typedef MySharedPointer<State> StatePtr;
    typedef MyPair<int, StatePtr> Id;
    typedef MyVector<StatePtr> Steps;
    typedef MyPair<char, Steps> Connection;
    typedef MyVector<Connection> Connections;
private:
    Connections connections;
    Id id;
public:
    //TODO: move??

    explicit State(int);

    State(int, const Connections &);

    State(int, const Connections &, char);

private:
    void setId(int);

public:

    bool contains(const std::string) const;

    StatePtr getPtr() const;

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

    //TODO: add &
    void addConnection(const Connection&);
};

