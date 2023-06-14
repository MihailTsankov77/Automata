#include <iostream>

#include "Automata.h"
int main() {

    Automata dfa;

    dfa.addState(0, begging);
    dfa.addState(2, begging);
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


    return 0;
}
