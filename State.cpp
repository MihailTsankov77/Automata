#include "State.h"

#include <utility>

State::State(int id) {
    setId(id);
}

State::State(int id, const State::Connections &connections) : State(id, connections, 0) {}

State::State(int id, const State::Connections &connections, char status) : connections(connections) {
    setId(id);
    this->status = status;
}


void State::setId(int _id) {
    id.setKey(_id);
    id.setValue(MySharedPointer<State>(this));
}

bool State::contains(std::string input) const {
    if (input.length() == 0) {
        return isFinal();
    }

    char next = input[0];
    std::string nextInput = input.substr(1);

    for (int i = 0; i < connections.size(); ++i) {
        if (connections[i].isThisKey(next)) {
            Steps nextSteps = connections[i].getValue();

            for (int j = 0; j < nextSteps.size(); ++j) {
                bool isAccepted = nextSteps[j]->contains(nextInput);

                if (isAccepted) {
                    return true;
                }
            }

            return false;
        }
    }

    return false;
}

State::~State() {
    id.getValue().reset();
}

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

void State::addConnection(const State::Connection& connection) {
    for (int i = 0; i < connections.size(); ++i) {
        if(connections[i].isThisKey(connection.getKey())){
            //TODO: implement concat
            Steps newSteps = connection.getValue();
            for (int j = 0; j < newSteps.size(); ++j) {
                connections[i].getValue().push(newSteps[i]);
            }

            return;
        }
    }

    connections.push(connection);
}

 State::StatePtr State::getPtr() const{
    return  StatePtr(id.getValue());
}

