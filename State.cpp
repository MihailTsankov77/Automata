#include "State.h"

#include <utility>

State::State(Id id) : State(id, 0) {}

State::State(Id id, char status) : id(id), status(status) {}


void State::makeStatus(StateStatus stat) {
    status = status | stat;
}

void State::makeNotStatus(StateStatus stat) {
    if (isStatus(stat)) {
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
                if (std::shared_ptr<State> thisStep = nextSteps[j].lock()) {

                    bool isAccepted = thisStep->accepts(nextInput);

                    if (isAccepted) {
                        return true;
                    }
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

void State::addConnections(const State::Connections &_connections) {
    //TODO: clean the indentical connections
    // TODO: implement Concat
    //TODO: do as addConnection refactor
    for (int i = 0; i < _connections.size(); ++i) {
        bool find = false;
        for (int j = 0; j < connections.size(); ++j) {
            if (connections[j].isThisKey(_connections[i].getKey())) {
                Steps steps = _connections[i].getValue();

                for (int k = 0; k < steps.size(); ++k) {
                    connections[j].getValue().push(steps[k]);
                }

                find = true;
                break;
            }
        }

        if (!find) {
            connections.push(_connections[i]);
        }
    }

    //TODO: use optimization
}

const State::Connections &State::getConnections() const {
    return connections;
}

State::Id State::getId() const {
    return id;
}

void State::printConnections() const {
    std::cout << id << " [";

    if (isBegging()) {
        std::cout << "beginning";
    }

    if (isFinal()) {
        if (isBegging()) {
            std::cout << "/";
        }
        std::cout << "final";
    } else if (!isBegging()) {
        std::cout << "-";
    }

    std::cout << "] " << ": ";


    for (int i = 0; i < connections.size(); ++i) {
        std::cout << connections[i].getKey() << " -> ";
        for (int j = 0; j < connections[i].getValue().size(); ++j) {
            if (std::shared_ptr<State> thisStep = connections[i].getValue()[j].lock()) {
                std::cout << thisStep->id;
                if (j < connections[i].getValue().size() - 1) {
                    std::cout << ", ";
                }
            }
        }
        std::cout << "; ";
    }
    std::cout << std::endl;
}

State::Connections State::optimizeConnections(const State::Connections &connections) {

    auto compare = [](const Step &a, const Step &b) {
        if (std::shared_ptr<State> stepA = a.lock()) {
            if (std::shared_ptr<State> stepB = b.lock()) {
                return stepA->id == stepB->id;
            }
        }

        return false;

    };


    Connections optimizedConnections;
    for (int i = 0; i < connections.size(); ++i) {
        bool letterExistAlready = false;

        for (int j = 0; j < optimizedConnections.size(); ++j) {
            if (connections[i].isThisKey(optimizedConnections[j].getKey())) {
                //TODO: implement concatUnique
                Steps currSteps = connections[i].getValue();
                for (int k = 0; k < currSteps.size(); ++k) {
                    if (optimizedConnections[j].getValue().count(currSteps[k], compare) == 0) {
                        optimizedConnections[j].getValue().push(currSteps[k]);
                    }
                }

                letterExistAlready = true;
                break;
            }
        }

        if (!letterExistAlready) {
            optimizedConnections.push(connections[i]);
        }

    }

    return optimizedConnections;
}

void State::changeStatus(char _status) {
    status = _status;
}

void State::changeId(State::Id _id) {
    id = _id;
}

char State::getStatus() const {
    return status;
}

//add erase weakPtr that don't have value and call this method on remove state
// use filter
