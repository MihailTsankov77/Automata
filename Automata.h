#pragma once

#include "State.h"
#include "BaseComponents/MySet.hpp"
#include "BaseComponents/MyString.h"

class Automata {
private:
    //TODO: remove
    typedef std::shared_ptr<State> StatePtr;
    typedef MyVector<StatePtr> States;
    States states;
    State::Alphabet alphabet;

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

    const State::Alphabet& getAlphabet() const;

    void printBeginningStates() const;
    void printFinalStates() const;

    void makeTotal();

private:
    size_t findState(State::Id) const;
    State::Id findSpareId() const;

    void assertIdDontExist(State::Id) const;

public:
    bool isEmpty() const;
    int statesSize() const;

    bool accepts(const MyString &) const;


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

    MyString getRegEx() const;
private:
    typedef MyVector<MyString> RegExes;
    typedef MyPair<State::Id, MyString> Path;
    typedef MyVector<Path> Paths;
    void createRegEx(Paths,  const StatePtr &, RegExes&) const;
    void checkForKleenePaths(Paths paths, const StatePtr &currentStep, State::Id searchId, RegExes &kleeneStartExes) const;

    typedef MySet<State::Id> OldIds;
    typedef MyPair<OldIds, StatePtr> IdStateMap;

    static StatePtr createDeterminizationState( MyVector<IdStateMap>&, State::Id&, const State::Steps&);

//    void cleanAutomata();
};


