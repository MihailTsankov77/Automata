#include "Automata.h"

Automata::Automata(size_t num) : states(num) {}

void Automata::addState(State::Id id) {
    addState(id, 0);
}

void Automata::addState(State::Id id, char status) {
    assertIdDontExist(id);

    states.push(StatePtr(new State(id, status)));
}

void Automata::deleteState(State::Id id) {
    size_t index = findState(id);

    //TODO: implement
//    states.erase(index, 1);
}

void Automata::addConnection(State::Id startId, char letter, State::Id endId) {
    size_t startIndex = findState(startId);
    size_t endIndex = findState(endId);

    states[startIndex]->addConnection(letter, State::Step(states[endIndex]));
}

size_t Automata::findState(State::Id id) const {
    for (int i = 0; i < states.size(); ++i) {
        if (states[i]->isSameId(id)) {
            return i;
        }
    }

    throw "TODO: write exeption: No such id!!";
}

void Automata::assertIdDontExist(State::Id id) const {
    for (int i = 0; i < states.size(); ++i) {
        if (states[i]->isSameId(id)) {
            throw "TODO: write exeption: there is this shit id!!";
        }
    }
}

bool Automata::isEmpty() const {
    return states.isEmpty();
}

bool Automata::accepts(const std::string& input) const {
    for (int i = 0; i < states.size(); ++i) {
        if(states[i]->isBegging()){
            bool accept = states[i]->accepts(input);

            if(accept){
                return true;
            }
        }
    }

    return false;
}

void Automata::makeBegging(State::Id id) {
    size_t index = findState(id);
    states[index]->makeBegging();
}

void Automata::makeNotBegging(State::Id id) {
    size_t index = findState(id);
    states[index]->makeNotBegging();
}

void Automata::makeFinal(State::Id id) {
    size_t index = findState(id);
    states[index]->makeFinal();
}

void Automata::makeNotFinal(State::Id id) {
    size_t index = findState(id);
    states[index]->makeNotFinal();
}


