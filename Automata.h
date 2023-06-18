#pragma once

#include "State.h"

//TODO: remove
#include <string>
#include <set>

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
    int statesSize() const;

    bool accepts(const std::string &) const;


public:
    static Automata onion(const Automata &, const Automata &);

    Automata& onion(const Automata &);

    static Automata kleeneStar(const Automata&);

    Automata& kleeneStar();

    static Automata kleenePlus(const Automata&);

    Automata& kleenePlus();

    static Automata concat(const Automata &, const Automata &);

    Automata& concat(const Automata &);

    void determinization();

    static Automata reverse(const Automata &);
    void reverse();

    static Automata minimize(const Automata&);
    Automata& minimize();

    void print()const;

    void changeStatusToState(State::Id, char);

    std::string getRegEx() const;
private:
    typedef MyVector<std::string> RegExes;
    typedef MyPair<State::Id, std::string> Path;
    typedef MyVector<Path> Paths;
    void createRegEx(Paths,  const StatePtr &, RegExes&) const;

    typedef std::set<State::Id> OldIds;
    typedef MyPair<OldIds, StatePtr> IdStateMap;



    static StatePtr createDeterminizationState( MyVector<IdStateMap>&, State::Id&, const State::Steps&);


//    void cleanAutomata();
};


