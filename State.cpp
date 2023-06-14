#include "State.h"

#include <utility>

State::State(Id id) : State(id, 0) {}

State::State(Id id, char status) : id(id), status(status) {}


void State::makeStatus(StateStatus stat) {
    status = status | stat;
}

void State::makeNotStatus(StateStatus stat) {
    if (isBegging()) {
        status = status ^ stat;
    }
}

bool State::isStatus(StateStatus stat) const {
    return status & stat;
}

void State::makeBegging() {
    makeStatus(begging);
}

void State::makeNotBegging() {
    makeNotStatus(begging);
}

bool State::isBegging() const {
    return isStatus(begging);
}

void State::makeFinal() {
    makeStatus(final);
}

void State::makeNotFinal() {
    makeNotStatus(final);
}

bool State::isFinal() const {
    return isStatus(final);
}

bool State::isSameId(Id _id) const {
    return id == _id;
}

void State::addConnection(char letter, const Step &step) {
    for (int i = 0; i < connections.size(); ++i) {
        if (connections[i].isThisKey(letter)) {
            connections[i].getValue().push(step);
            return;
        }
    }

    Steps newSteps;
    newSteps.push(step);
    connections.push(Connection(letter, newSteps));
}

bool State::accepts(std::string input) const {
    if (input.length() == 0) {
        return isFinal();
    }

    char next = input[0];
    std::string nextInput = input.substr(1);

    for (int i = 0; i < connections.size(); ++i) {
        if (connections[i].isThisKey(next)) {
            Steps nextSteps = connections[i].getValue();

            for (int j = 0; j < nextSteps.size(); ++j) {
                if(nextSteps[j].expired()){
                    continue;
                }

                std::shared_ptr<State> thisStep = nextSteps[j].lock();

                bool isAccepted = thisStep->accepts(nextInput);

                if (isAccepted) {
                    return true;
                }
            }

            return false;
        }
    }

    return false;
}

void State::removeConnection(char letter, size_t index) {
    //TODO: implement
}

void State::cleanConnections() {
    //TODO: implement
}

