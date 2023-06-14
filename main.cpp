#include <iostream>
#include "State.h"
#include <string>

int main() {
    std::string input = "aaaab";

    State start(0, State::Connections(0), begging);
    State state1(0, State::Connections(0),  final);

    // a*
    State::Steps steps0(1);
    steps0.push(start.getPtr());

    start.addConnection(State::Connection('a', steps0));

    //a*b
    State::Steps steps1(1);
    steps1.push(state1.getPtr());

    start.addConnection(State::Connection('b', steps1));

    if(start.contains(input)){
        std::cout<<"opaa";
    }else{
        std::cout<<"keke";
    }
    return 0;
}
