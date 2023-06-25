#include "Main/State.h"

#include <utility>
#include <fstream>

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

void State::makeBeginning() {
    makeStatus(beginning);
}

void State::makeNotBeginning() {
    makeNotStatus(beginning);
}

bool State::isBeginning() const {
    return isStatus(beginning);
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
                if (SharedPtr<State> thisStep = nextSteps[j].lock()) {

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

void State::addConnections(const State::Connections &_connections) {
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
}

const State::Connections &State::getConnections() const {
    return connections;
}

State::Id State::getId() const {
    return id;
}

void State::printConnections() const {
    std::cout << id << " [";

    if (isBeginning()) {
        std::cout << "beginning";
    }

    if (isFinal()) {
        if (isBeginning()) {
            std::cout << "/";
        }
        std::cout << "final";
    } else if (!isBeginning()) {
        std::cout << "-";
    }

    std::cout << "] " << ": ";


    for (int i = 0; i < connections.size(); ++i) {
        std::cout << connections[i].getKey() << " -> ";
        for (int j = 0; j < connections[i].getValue().size(); ++j) {
            if (SharedPtr<State> thisStep = connections[i].getValue()[j].lock()) {
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
        if (SharedPtr<State> stepA = a.lock()) {
            if (SharedPtr<State> stepB = b.lock()) {
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


void State::makeTotal(const Alphabet &alphabet, const Step &step) {
    for (int i = 0; i < alphabet.size(); ++i) {
        bool exist = false;
        for (int j = 0; j < connections.size(); ++j) {
            if (connections[j].getKey() == alphabet[i]) {
                exist = true;
                break;
            }
        }
        if (!exist) {
            addConnection(alphabet[i], step);
        }
    }
}

bool State::isDeterministicState() const {
    for (int i = 0; i < connections.size(); ++i) {
        if (connections[i].getValue().size() > 1) {
            return false;
        }
    }

    return true;
}

bool State::acceptsWords() const {
    MySet<Id> ids;
   return acceptsWordsPr(ids);
}

bool State::acceptsWordsPr(MySet<Id> & ids) const {
    if(ids.contains(getId())){
        return false;
    }

    ids.push(getId());

    if(isFinal()){
        return true;
    }



    for (int i = 0; i < connections.size(); ++i) {
        Steps nextSteps = connections[i].getValue();

        for (int j = 0; j < nextSteps.size(); ++j) {
            if (SharedPtr<State> thisStep = nextSteps[j].lock()) {

                if (thisStep->acceptsWordsPr(ids)) {
                    return true;
                }
            }
        }
    }

    return false;
}

void State::saveConnections(std::fstream &file) const {
    for (int i = 0; i < connections.size(); ++i) {
        Connection connection = connections[i];
        for (int j = 0; j < connection.getValue().size(); ++j) {
            if (SharedPtr<State> thisStep = connection.getValue()[j].lock()){
                file.write((const char*) &id, sizeof(State::Id));
                char letter = connection.getKey();
                file.write( &letter, sizeof(State::Id));
                Id stepId = thisStep->id;
                file.write((const char*) &stepId, sizeof(State::Id));
            }
        }
    }
}
