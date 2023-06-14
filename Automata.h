#pragma once

#include "State.h"

//TODO: remove
#include <string>

class Automata {
private:
    //TODO: remove
    typedef std::shared_ptr<State> StatePtr;
    typedef MyVector<StatePtr> States;
    States states;

public:
    Automata() = default;

    explicit Automata(size_t);

    //TODO: move??
    void addState(State::Id);

    void addState(State::Id, char);

    void makeBegging(State::Id);

    void makeNotBegging(State::Id);

    void makeFinal(State::Id);

    void makeNotFinal(State::Id);

    void deleteState(State::Id);

    void addConnection(State::Id, char, State::Id);

private:
    size_t findState(State::Id) const;
    State::Id findSpareId() const;

    void assertIdDontExist(State::Id) const;

public:
    bool isEmpty() const;

    bool accepts(const std::string &) const;


public:
    static Automata onion(const Automata &, const Automata &);

    void onion(const Automata &);

    static Automata kleeneStar(const Automata&);

    void kleeneStar();

private:
//    void cleanAutomata();
};


