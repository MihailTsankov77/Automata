#include <iostream>

#include "Automata.h"

bool _PRINT_ = true;

void basicTest() {
    Automata dfa;

    dfa.addState(0, final | begging);

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

    dfa.addState(0, final | begging);

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

    dfa1.addState(0, begging);
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

    dfa1.addState(0, begging);
    dfa1.addState(1, final);

    dfa1.addConnection(0, 'a', 1);
    dfa1.addConnection(1, 'b', 1);

    Automata dfa2;

    dfa2.addState(0, begging);
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

    n.addState(0, begging);
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

    std::string input = "abaaaacabaa";
    if (_PRINT_) {
        if (n.accepts(input)) {
            std::cout << "Accept not det -> ";
        } else {
            std::cout << "Dont accept not det -> ";
        }
    }

    n.determinization();

    if (_PRINT_) {
        if (n.accepts(input)) {
            std::cout << "accept det" << std::endl;
        } else {
            std::cout << "dont accept det" << std::endl;
        }

        n.print();
    }
}

void reverseTest() {
    Automata dfa;

    dfa.addState(0, begging);

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
}


//TODO: move to factory function

void printRules() {
    std::cout << "A -> K | P | U | BA | ø" << std::endl;
    std::cout << "K -> (A)*" << std::endl;
    std::cout << "P -> (A)+" << std::endl;
    std::cout << "U -> (A+A)" << std::endl;
    std::cout << "B -> ALPHABET" << std::endl;
}


Automata createAutomata(std::string regEx, bool isFirst = true) {
    Automata toReturn;
    State::Id _ID = 0;

    char status = 0;
    if (isFirst) {
        status = begging;
    }

    if (regEx.empty()) {
        status |= final;
    }

    toReturn.addState(_ID++, status);


    while (!regEx.empty()) {
        char next = regEx[0];
        regEx.erase(0, 1);
        switch (next) {
            case '(':{

            }
            case ')':{
                // * +
                continue;
            }
            default: {
                //is alphabet TODO
                toReturn.addState(_ID++, regEx.empty() ? final : 0);
                toReturn.addConnection(_ID - 2, next, _ID - 1);

            }
        }


    }

    return toReturn;
}

int main() {

//    Automata test = createAutomata("abcs");
//
//            if(test.accepts("abcs")){
//                std::cout<<"BLob";
//            }
//
//    return 0;


    Automata ab(3);
    ab.addState(0, begging);
    ab.addState(-1);
    ab.addState(2, final);

    ab.addConnection(0, 'a', -1);
    ab.addConnection(-1, 'b', 2);

    Automata ba = Automata::reverse(ab);
//    ba.print();

    Automata cd(3);
    cd.addState(0, begging);
    cd.addState(1);
    cd.addState(2, final);

    cd.addConnection(0, 'c', 1);
    cd.addConnection(1, 'd', 2);

    cd.kleeneStar();
//    cd.print();
//    Automata::kleeneStar(cd);

    Automata big = Automata::concat(Automata::concat(ab, cd), ba);
//    big.reverse();
    big.print();
//
//
//
//    if(big.accepts("abba")){
//        std::cout<<"yessir"<<std::endl;
//    }else{
//        std::cout<<"stupid"<<std::endl;
//    }
//
//    if(big.accepts("ab")){
//        std::cout<<"stupid2"<<std::endl;
//    }else{
//        std::cout<<"yessir2"<<std::endl;
//    }


    return 0;
}

