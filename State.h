#pragma once

#include "BaseComponents/MyVector.hpp"
#include "BaseComponents/MyPair.hpp"
#include "BaseComponents/MySet.hpp"
#include "BaseComponents/MyWeakPtr.hpp"

//TODO: switch
#include <string>
#include <vector>

enum StateStatus {
    final = 1,
    beginning = 2
};

class State {
public:
    typedef int Id;

    typedef WeakPtr<State> Step;
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

    typedef MySet<char> Alphabet;

    void makeTotal(const Alphabet &, const Step &);

    bool isDeterministicState() const;

    bool acceptsWords() const;

private:
    bool acceptsWordsPr(MySet<Id>&) const;
    char status = 0;

    void makeStatus(StateStatus);

    void makeNotStatus(StateStatus);

    bool isStatus(StateStatus) const;

public:
    void makeBeginning();

    void makeNotBeginning();

    bool isBeginning() const;

    void makeFinal();

    void makeNotFinal();

    bool isFinal() const;

    void addConnection(char, const Step &);

    void addConnections(const Connections &);

    const Connections &getConnections() const;

    void printConnections() const;

    static Connections optimizeConnections(const Connections &);

};

