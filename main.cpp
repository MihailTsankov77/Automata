#include <iostream>

#include "Main/Automata.h"
#include "Factory/AutomataInterface.h"
#include "Factory/Parsers/RegExParser.h"

//TESTS
bool _PRINT_ = true;

void basicTest() {
    Automata dfa;

    dfa.addState(0, final | beginning);

    dfa.addState(1, final);
    dfa.addState(2);

    dfa.addConnection(0, 'a', 0);
    dfa.addConnection(0, 'b', 1);
    dfa.addConnection(0, 'b', 2);
    dfa.addConnection(1, 'b', 1);
    dfa.addConnection(2, 'c', 1);
    dfa.addConnection(2, 'c', 0);


    if (_PRINT_) {
        if (dfa.accepts("aaaaabc")) {
            std::cout << "ura" << std::endl;
        } else {
            std::cout << "keke" << std::endl;
        }
    }

}

void clearUselessTests() {
    Automata dfa;

    dfa.addState(0, final | beginning);

    dfa.addState(1, final);
    dfa.addState(2);

    dfa.addConnection(0, 'a', 0);
    dfa.addConnection(0, 'b', 1);
    dfa.addConnection(1, 'b', 1);
    dfa.addConnection(2, 'c', 1);
    dfa.addConnection(2, 'c', 0);


    if (_PRINT_) {
        dfa.print();
    }


}

void unionTest() {
    Automata dfa1;

    dfa1.addState(0, beginning);
    dfa1.addState(1, final);

    dfa1.addConnection(0, 'a', 1);
    dfa1.addConnection(1, 'b', 1);

    Automata dfa2;

    dfa2.addState(0, beginning);
    dfa2.addState(1, final);

    dfa2.addConnection(0, 'a', 1);
    dfa2.addConnection(1, 'c', 1);


    Automata dfa = Automata::onion(dfa1, dfa2);
    if (_PRINT_) {
        if (dfa.accepts("accc") && dfa.accepts("abbb")) {
            std::cout << "ura" << std::endl;
        } else {
            std::cout << "keke" << std::endl;
        }
    }
}

void kleeneStarTest() {
    Automata dfa1;

    dfa1.addState(0, beginning);
    dfa1.addState(1);
    dfa1.addState(2, final);

    dfa1.addConnection(0, 'a', 1);
    dfa1.addConnection(1, 'b', 2);


    Automata dfa = Automata::kleeneStar(dfa1);
    if (_PRINT_) {
        if (dfa.accepts("abab")) {
            std::cout << "ura" << std::endl;
        } else {
            std::cout << "keke" << std::endl;
        }
    }
}

void concatTest() {
    Automata dfa1;

    dfa1.addState(0, beginning);
    dfa1.addState(1, final);

    dfa1.addConnection(0, 'a', 1);
    dfa1.addConnection(1, 'b', 1);

    Automata dfa2;

    dfa2.addState(0, beginning);
    dfa2.addState(1, final);

    dfa2.addConnection(0, 'a', 1);
    dfa2.addConnection(1, 'c', 1);


    Automata dfa = Automata::concat(dfa1, dfa2);
    if (_PRINT_) {
        if (dfa.accepts("abbbbbaccccc")) {
            std::cout << "ura" << std::endl;
        } else {
            std::cout << "keke" << std::endl;
        }
    }
}

void detTest() {
    Automata n;

    n.addState(0, beginning);
    n.addState(1);
    n.addState(2);
    n.addState(3, final);

    n.addConnection(0, 'a', 0);
    n.addConnection(0, 'b', 0);
    n.addConnection(0, 'c', 0);

    n.addConnection(0, 'c', 1);
    n.addConnection(1, 'a', 2);
    n.addConnection(2, 'b', 3);

    n.addConnection(3, 'a', 3);
    n.addConnection(3, 'b', 3);
    n.addConnection(3, 'c', 3);


    if (_PRINT_) {
        if (n.accepts("abaaaacabaa")) {
            std::cout << "Accept not det -> ";
        } else {
            std::cout << "Dont accept not det -> ";
        }
    }

    n.determine();
    if (_PRINT_) {
        if (n.accepts("abaaaacabaa")) {
            std::cout << "accept det" << std::endl;
        } else {
            std::cout << "dont accept det" << std::endl;
        }

        n.print();
    }
}

void reverseTest() {
    Automata dfa;

    dfa.addState(0, beginning);

    dfa.addState(1);
    dfa.addState(2);
    dfa.addState(3, final);

    dfa.addConnection(0, 'a', 1);
    dfa.addConnection(0, 'b', 2);
    dfa.addConnection(1, 'c', 3);
    dfa.addConnection(2, 'a', 3);


    if (_PRINT_) {
        if (dfa.accepts("ac") && dfa.accepts("ba")) {
            std::cout << "Accept -> ";
        } else {
            std::cout << "Don't accept -> ";
        }
    }

    Automata dfaReverse = Automata::reverse(dfa);

    if (_PRINT_) {
        if (dfaReverse.accepts("ca") && dfaReverse.accepts("ab")) {
            std::cout << " Reverse Accept" << std::endl;
        } else {
            std::cout << "Reverse Don't accept" << std::endl;
        }

        dfaReverse.print();
    }
}

void regExTest(){

    Automata reg;

    reg.addState(0, beginning);
    reg.addState(1, final);
    reg.addState(2);
    reg.addState(3 , final);

    reg.addConnection(0, 'a', 1);
    reg.addConnection(1, 'b', 2);
    reg.addConnection(2, 'b', 1);
    reg.addConnection(1, 'a', 3);

    reg.makeTotal();

    if(_PRINT_) {
        reg.print();
        reg.printBeginningStates();

        std::cout << reg.getRegEx() << std::endl;
    }
}

void theDeathTest(void(*fun)()) {
    _PRINT_ = false;
    while (true) {
        fun();
    }
}

void allTests() {
    basicTest();
    clearUselessTests();
    unionTest();
    kleeneStarTest();
    concatTest();
    detTest();
    regExTest();
}

void consoleInput(){
    while (AutomataInterface::getInstance().readCommand()){}
}


int main() {
//    regExTest();

//    allTests();
//    theDeathTest(allTests);

//    consoleInput();

    Automata ndfa = RegExParser::getInstance().parse("aaaba");

    ndfa.print();

    ndfa.minimize().print();
    std::cout<<ndfa.getRegEx();
    return 0;
}


