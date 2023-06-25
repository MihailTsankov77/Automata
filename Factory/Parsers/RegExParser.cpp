

#include "RegExParser.h"

RegExParser &RegExParser::getInstance() {
    static RegExParser factory;
    return factory;
}

Automata RegExParser::parse(const MyString &regEx) const {
    MyString reg = regEx;
    return createAutomata(reg);
}

void RegExParser::printRules() const {
    std::cout << "A -> K | U | BA | ø" << std::endl;
    std::cout << "K -> (A)*" << std::endl;
    std::cout << "U -> (A+A)" << std::endl;
    std::cout << "B -> ALPHABET" << std::endl;
}

bool RegExParser::isAlphabet(char a) const {
    return a >= 'a' && a <= 'z';
}

Automata RegExParser::createAutomata(MyString &regEx, bool hasOpenBracket) const {
    Automata toReturn;
    State::Id id = 0;

    if (regEx.isEmpty()) {
        return toReturn;
    }

    toReturn.addState(id++, beginning | final);

    while (!regEx.isEmpty()) {
        char next = regEx[0];
        regEx = regEx.substr(1, regEx.length()-1);

        switch (next) {
            case '(': {
                toReturn.concat(createAutomata(regEx, true));

                toReturn.concat(createAutomata(regEx, false));
                if (hasOpenBracket && regEx[0] == ')') {
                    break;
                } else {
                    return toReturn;
                }
            }
            case ')': {
                if (!hasOpenBracket) {
                    regEx = ')' + regEx;
                    return toReturn;
                }

                char symbol = regEx[0];

                switch (symbol) {
                    case '*': {
                        regEx = regEx.substr(1, regEx.length()-1);
                        toReturn.kleeneStar();
                        break;
                    }
                }

                return toReturn;
            }
            case '+': {
                return toReturn.onion(createAutomata(regEx, true));
            }
            default: {
                if (!isAlphabet(next)) {
                    throw "error";
                }

                toReturn.makeNotFinal(id - 1);
                toReturn.addState(id++, final);
                toReturn.addConnection(id - 2, next, id - 1);
            }
        }
    }

    return toReturn;
}