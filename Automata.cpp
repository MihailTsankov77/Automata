#include "Automata.h"

//TODO: remove
template<typename T>
T get_nth_element(std::set<T> &set_name, int index) {

    T toReturn;
    if (set_name.size() > index) {
        auto it = next(set_name.begin(), index);
        toReturn = *it;
    }

    return toReturn;
}

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

bool Automata::accepts(const std::string &input) const {
    for (int i = 0; i < states.size(); ++i) {
        if (states[i]->isBegging()) {
            bool accept = states[i]->accepts(input);

            if (accept) {
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

Automata Automata::onion(const Automata &left, const Automata &right) {
    Automata toReturn = left;
    toReturn.onion(right);
    return toReturn;
}

Automata &Automata::onion(const Automata &other) {
    for (int i = 0; i < other.states.size(); ++i) {
        // TODO: implement clone on sharePtr and use it
        states.push(other.states[i]);
        states[states.size() - 1]->changeId(findSpareId());
    }

    return *this;
}

Automata Automata::kleeneStar(const Automata &other) {
    return Automata(other).kleeneStar();
}

Automata &Automata::kleeneStar() {
    State::Id id = findSpareId();
    State::Connections allBeggingConnections;
    for (int i = 0; i < states.size(); ++i) {
        if (states[i]->isBegging()) {
            StatePtr begging = states[i];
            begging->makeNotBegging();

            State::Connections beggingConnections = begging->getConnections();

            //TODO: implement concat
            for (int j = 0; j < beggingConnections.size(); ++j) {
                allBeggingConnections.push(beggingConnections[j]);
            }
        }
    }

    addState(id, begging | final);

    for (int i = 0; i < states.size(); ++i) {
        if (states[i]->isFinal()) {
            states[i]->addConnections(allBeggingConnections);
        }
    }

// TODO
//    cleanAutomata();
    return *this;
}

State::Id Automata::findSpareId() const {
    State::Id id = -1;
    while (true) {
        try {
            assertIdDontExist(id);
            return id;
        } catch (...) {
            --id;
        }
    }
}

Automata Automata::concat(const Automata &left, const Automata &right) {
    Automata toReturn = left;
    toReturn.concat(right);
    return toReturn;
}

Automata &Automata::concat(const Automata &other) {
    State::Connections allBeggingConnections;
    bool hasFinalBegging = other.states.size() == 0;


    //TODO use clone of state sharePtr clone and defined copy constructor to ...
    //TODO use clone of state sharePtr clone
    Automata toConcat = other;

    for (int i = 0; i < toConcat.states.size(); ++i) {

        if (toConcat.states[i]->isBegging()) {
            StatePtr begging = toConcat.states[i];
            begging->makeNotBegging();

            if (!hasFinalBegging && begging->isFinal()) {
                hasFinalBegging = true;
            }

            State::Connections beggingConnections = begging->getConnections();

            //TODO: implement concat
            for (int j = 0; j < beggingConnections.size(); ++j) {
                allBeggingConnections.push(beggingConnections[j]);
            }
        }
    }

    for (int i = 0; i < states.size(); ++i) {
        if (states[i]->isFinal()) {
            if (!hasFinalBegging) {
                states[i]->makeNotFinal();
            }

            states[i]->addConnections(allBeggingConnections);
        }
    }

    //TODO: concat

    for (int i = 0; i < toConcat.states.size(); ++i) {
        //TODO add only if there is more then one ptr pointing to it
        toConcat.states[i]->changeId(findSpareId());
        states.push(toConcat.states[i]);
    }

    // TODO
//    cleanAutomata();

    return *this;
}
//TODO make [] = to resize

void Automata::determinization() {

    State::Connections beginningStatesConnections;

    char begStatus = begging;

    OldIds oldIds;
    for (int i = 0; i < states.size(); ++i) {
        if (states[i]->isBegging()) {
            //TODO: implement concat
            State::Connections stateConnections = states[i]->getConnections();
            for (int j = 0; j < stateConnections.size(); ++j) {
                beginningStatesConnections.push(stateConnections[j]);
            }

            if (states[i]->isFinal()) {
                begStatus = begStatus | final;
            }

            oldIds.insert(states[i]->getId());
        }
    }

    MyVector<IdStateMap> newStatesIds;

    newStatesIds.push(IdStateMap(oldIds, StatePtr(new State(0, begStatus))));

    State::Connections optimizedConnections = State::optimizeConnections(beginningStatesConnections);
    State::Id currentId = 1;

    for (int i = 0; i < optimizedConnections.size(); ++i) {
        newStatesIds[0].getValue()->addConnection(optimizedConnections[i].getKey(),
                                                  createDeterminizationState(newStatesIds, currentId,
                                                                             optimizedConnections[i].getValue()));
    }


    States newStates(newStatesIds.size());
    for (int i = 0; i < newStatesIds.size(); ++i) {
        newStates.push(newStatesIds[i].getValue());
    }

    states = newStates;
}


Automata::StatePtr Automata::createDeterminizationState(MyVector<IdStateMap> &newStatesIds, State::Id &currentId,
                                                        const State::Steps &steps) {
    State::Id _ID = currentId;



    //check if already exist this state
    int existAlreadyId = -1;
    for (int i = 0; i < newStatesIds.size(); ++i) {
        OldIds existingStateIds = newStatesIds[i].getKey();

        std::set<int> currentStepIds;
        for (int j = 0; j < steps.size(); ++j) {
            if (std::shared_ptr<State> thisStep = steps[j].lock()) {

                currentStepIds.insert(thisStep->getId());
            }

        }

        for (int k = 0; k < currentStepIds.size() && existingStateIds.size() == currentStepIds.size(); ++k) {

            //TODO: create [] on your set
            if (!existingStateIds.count(get_nth_element(currentStepIds, k))) {
                existAlreadyId = -1;
                break;
            } else {
                existAlreadyId = i;
            }
        }

        if (existAlreadyId >= 0) {
            break;
        }

    }

    if (existAlreadyId >= 0) {
        return newStatesIds[existAlreadyId].getValue();
    }

    char status = 0;
    State::Connections statesConnections;

    OldIds oldIds;
    for (int i = 0; i < steps.size(); ++i) {

        if (std::shared_ptr<State> thisStep = steps[i].lock()) {

            //TODO: implement concat
            State::Connections stateConnections = thisStep->getConnections();
            for (int j = 0; j < stateConnections.size(); ++j) {
                statesConnections.push(stateConnections[j]);
            }

            if (thisStep->isFinal()) {
                status = final;
            }

            oldIds.insert(thisStep->getId());
        }
    }


    newStatesIds.push(IdStateMap(oldIds, StatePtr(new State(_ID, status))));

    State::Connections optimizedConnections = State::optimizeConnections(statesConnections);
    ++currentId;
    for (int i = 0; i < optimizedConnections.size(); ++i) {
        newStatesIds[_ID].getValue()->addConnection(optimizedConnections[i].getKey(),
                                                    createDeterminizationState(newStatesIds, currentId,
                                                                               optimizedConnections[i].getValue()));
    }


    return newStatesIds[_ID].getValue();
}

void Automata::print() const {
    for (int i = 0; i < states.size(); ++i) {
        states[i]->printConnections();
    }
}

Automata Automata::reverse(const Automata &other) {
    Automata reverseAutomata(other.states.size());

    for (int i = 0; i < other.states.size(); ++i) {
        reverseAutomata.addState(other.states[i]->getId());
        if (other.states[i]->isBegging()) {
            reverseAutomata.states[i]->makeFinal();
        }
        if (other.states[i]->isFinal()) {
            reverseAutomata.states[i]->makeBegging();
        }
    }

    for (int i = 0; i < other.states.size(); ++i) {
        State::Id id = other.states[i]->getId();
        State::Connections connections = other.states[i]->getConnections();
        for (int j = 0; j < connections.size(); ++j) {
            for (int k = 0; k < connections[j].getValue().size(); ++k) {
                if (std::shared_ptr<State> thisStep = connections[j].getValue()[k].lock()) {
                    reverseAutomata.addConnection(thisStep->getId(), connections[j].getKey(), id);
                }
            }
        }
    }

    return reverseAutomata;
}

void Automata::reverse() {
    Automata reverse = Automata::reverse(*this);

    *this = reverse;
}

Automata Automata::minimize(const Automata &other) {
    Automata mini = other;
    return mini.minimize();
}

Automata &Automata::minimize() {
    for (int i = 0; i < 2; ++i) {
        reverse();
        determinization();
    }

    return *this;
}

void Automata::changeStatusToState(State::Id id, char status) {
    size_t index = findState(id);

    states[index]->changeStatus(status);
}

int Automata::statesSize() const {
    return states.size();
}

std::string Automata::getRegEx() const {

    RegExes regExes;

    for (int i = 0; i < states.size(); ++i) {
        if (states[i]->isBegging()) {
            createRegEx(Paths(), states[i], regExes);
        }
    }

    std::string regEx;

    for (int i = 0; i < regExes.size(); ++i) {
        if (i == 0) {
            regEx = regExes[i];
        } else {
            regEx = "(" + regEx + "+" + regExes[i] + ")";
        }
    }

    return regEx;
}

void Automata::createRegEx(Automata::Paths paths, const StatePtr &currentStep, Automata::RegExes &regExes) const {

    paths.push(Path(currentStep->getId(), ""));

    typedef MyVector<std::string> KleeneStarParts;
    KleeneStarParts kleeneStarParts;
    State::Connections notKleeneStarConnections;

    for (int i = 0; i < currentStep->getConnections().size(); ++i) {
        State::Connection connection = currentStep->getConnections()[i];

        for (int j = 0; j < connection.getValue().size(); ++j) {
            bool isKleene = false;
            if (std::shared_ptr<State> thisStep = connection.getValue()[j].lock()) {
                for (int k = 0; k < paths.size(); ++k) {
                    if (paths[k].getKey() == thisStep->getId()) {
                        //kleene star
                        kleeneStarParts.push(connection.getKey() + paths[k].getValue());
                        isKleene = true;
                        break;
                    }
                }
            }

            if (!isKleene) {
                notKleeneStarConnections.push(connection);
            }
        }
    }


    //create kleene part
    std::string kleeneStarExp;
    for (int i = 0; i < kleeneStarParts.size(); ++i) {
        if (i == 0) {
            kleeneStarExp = kleeneStarParts[i];
        } else {
            kleeneStarExp = "(" + kleeneStarExp + "+" + kleeneStarParts[i] + ")";
        }
    }

    kleeneStarExp = "(" + kleeneStarExp + ")*";

    //update paths

    for (int i = 0; i < paths.size() && kleeneStarParts.size() != 0; ++i) {
        paths[i].getValue() += kleeneStarExp;
    }

    //add if final
    bool shouldAddLetter = true;

    if (currentStep->isFinal()) {
        if (paths[0].getValue().length() != 0) {
            regExes.push(paths[0].getValue());
        } else {
            shouldAddLetter = false;
        }
    }

    //recursion
    for (int i = 0; i < notKleeneStarConnections.size(); ++i) {
        State::Connection connection = notKleeneStarConnections[i];

        for (int j = 0; j < connection.getValue().size(); ++j) {
            if (std::shared_ptr<State> thisStep = connection.getValue()[j].lock()) {

                if (shouldAddLetter) {
                    paths[paths.size() - 1].getValue() += connection.getKey();
                }

                createRegEx(paths, thisStep, regExes);

            }
        }
    }


}


// TODO: Questionable
//void Automata::cleanAutomata() {
//    for (int i = 0; i < states.size(); ++i) {
//        //TODO: fix
//        State::Step step = states[i];
//        if(!states[i]->isBegging() && step->)
//    }
//}


//TODO: redefine copy const with share ptr clone