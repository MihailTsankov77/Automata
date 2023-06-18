#pragma once

#include "BaseComponents/MyVector.hpp"
#include "BaseComponents/MyPair.hpp"
#include "BaseComponents/SharePtr.hpp"
//TODO: switch
#include <string>
#include <vector>
#include <set>

enum StateStatus {
    final = 1,
    begging = 2
};

class State {
public:
    typedef int Id;

    typedef std::weak_ptr<State> Step;
    typedef MyVector<Step> Steps;
    typedef MyPair<char, Steps> Connection;
    typedef MyVector<Connection> Connections;
private:
    Id id;
    Connections connections;
public:
    //TODO: move??

    //TODO: write copy constr with clone ptr
    explicit State(Id);

    explicit State(Id, char);

public:
    bool accepts(std::string) const;

    bool isSameId(Id) const;

    State::Id getId() const;

    void changeStatus(char);

    void changeId(State::Id);

    char getStatus() const;

    typedef std::set<char> Alphabet;
    void makeTotal(const Alphabet&,const Step&);

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

    void addConnection(char, const Step &);

    void addConnections(const Connections &);

    void removeConnection(char, size_t);

    void cleanConnections();

    const Connections &getConnections() const;

    void printConnections() const;

    static Connections optimizeConnections(const Connections&);

};

