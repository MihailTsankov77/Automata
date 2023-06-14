#pragma once

#include "BaseComponents/MyVector.hpp"
#include "BaseComponents/MyPair.hpp"
#include "BaseComponents/SharePtr.hpp"
//TODO: switch
#include <string>
#include <vector>

enum StateStatus {
    final = 1,
    begging = 2
};

class State {
public:
    typedef State* StatePtr;
    typedef MyVector<StatePtr> Steps;
    typedef MyPair<char, Steps> Connection;
    typedef MyVector<Connection> Connections;
private:
    Connections connections;
public:
    //TODO: move??

    explicit State();

    State( const Connections &);

    State( const Connections &, char);

public:

    bool contains(const std::string) const;
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

