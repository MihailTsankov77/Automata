#include <iostream>

#include "Automata.h"

void basicTest(){
    Automata dfa;

    dfa.addState(0, begging);
    dfa.addState(2);
    dfa.addState(1, final);


    dfa.addConnection(0, 'a', 0);
    dfa.addConnection(0, 'b', 1);
    dfa.addConnection(1, 'b', 1);
    dfa.addConnection(2, 'c', 1);
    dfa.addConnection(2, 'c', 0);

    std::string input = "caaaaab";

    if (dfa.accepts(input)) {
        std::cout << "ura";
    } else {
        std::cout << "keke";
    }
}

void unionTest(){
    Automata dfa1;

    dfa1.addState(0, begging);
    dfa1.addState(1, final);

    dfa1.addConnection(0, 'a', 1);
    dfa1.addConnection(1, 'b', 1);

    Automata dfa2;

    dfa2.addState(0, begging);
    dfa2.addState(1, final);

    dfa2.addConnection(0, 'a', 1);
    dfa2.addConnection(1, 'c', 1);


    Automata dfa = Automata::onion(dfa1, dfa2);

    if (dfa.accepts("accc") && dfa.accepts("abbb")) {
        std::cout << "ura";
    } else {
        std::cout << "keke";
    }
}



int main() {



    return 0;
}

