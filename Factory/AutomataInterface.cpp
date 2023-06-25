
#include "AutomataInterface.h"
#include "Files/FileManager.h"
#include "Parsers/RegExParser.h"

AutomataInterface &AutomataInterface::getInstance() {
    static AutomataInterface factory;
    return factory;
}

bool AutomataInterface::readCommand() {
    std::cout << "Choose command from: " << Commands::accepts << " to " << Commands::terminate << std::endl;
    int command;
    std::cin >> command;
    switch (command) {
        case accepts :
        case getRegEx:
        case kleeneStar:
        case determine:
        case minimize:
        case reverse:
        case total:
        case print: {
            oneItemCommand(command);
            break;
        }
        case concat:
        case onion: {
            twoItemCommand(command);
            break;
        }
        case createFromText: {
            std::cout << "FilePath:";
            std::string filePath;
            std::cin >> filePath;
            automates.push(FileManager::getInstance().readFromFile(filePath));
            break;
        }
        case saveInFile: {
            std::cout << "FilePath:";
            std::string filePath;
            std::cin >> filePath;

            std::cout << "Choose automate id from " << 0 << " to " << automates.size() - 1 << std::endl;
            size_t id;
            std::cin >> id;
            if (id >= automates.size()) {
                return true;
            }

            FileManager::getInstance().saveInFile(filePath, automates[id]);
            break;
        }
        case createFromRegEx: {
            std::cout << "Write reg exp following the rules:" << std::endl;
            RegExParser::getInstance().printRules();
            std::string regEx;
            std::cin>>regEx;

            automates.push(RegExParser::getInstance().parse(regEx));

            break;
        }


        case info:{
            std::cout<<"accepts : "<<accepts<<std::endl;
            std::cout<<"createFromText : "<<createFromText<<std::endl;
            std::cout<<"saveInFile : "<<saveInFile<<std::endl;
            std::cout<<"createFromRegEx : "<<createFromRegEx<<std::endl;
            std::cout<<"getRegEx : "<<getRegEx<<std::endl;
            std::cout<<"concat : "<<concat<<std::endl;
            std::cout<<"onion : "<<onion<<std::endl;
            std::cout<<"kleeneStar : "<<kleeneStar<<std::endl;
            std::cout<<"determine : "<<determine<<std::endl;
            std::cout<<"minimize : "<<minimize<<std::endl;
            std::cout<<"reverse : "<<reverse<<std::endl;
            std::cout<<"print : "<<print<<std::endl;
            std::cout<<"total : "<<total<<std::endl;
            std::cout<<"info : "<<info<<std::endl;
            std::cout<<"terminate : "<<terminate<<std::endl;

            return true;
        }

        case terminate: {
            return false;
        }
    }

    return true;
}

void AutomataInterface::oneItemCommand(int command) {
    std::cout << "Choose automate id from " << 0 << " to " << automates.size() - 1 << std::endl;
    size_t id;
    std::cin >> id;

    if (id >= automates.size()) {
        return;
    }
    switch (command) {
        case accepts : {
            std::string input;
            std::cin >> input;
            if (automates[id].accepts(input)) {
                std::cout << "Accepts!";
            } else {
                std::cout << "Dont Accepts!";
            }
            return;
        }
        case getRegEx: {
            std::cout << automates[id].getRegEx();
            return;
        }
        case determine: {
            automates[id].determine();
            return;
        }
        case minimize: {
            automates[id].minimize();
            return;
        }
        case reverse: {
            automates[id].reverse();
            return;
        }
        case print: {
            automates[id].print();
            return;
        }
        case kleeneStar: {
            automates[id].kleeneStar();
            return;
        }
        case total: {
            automates[id].makeTotal();
            return;
        }
    }
}

void AutomataInterface::twoItemCommand(int command) {
    std::cout << "Choose two automate ids from " << 0 << " to " << automates.size() - 1 << std::endl;
    size_t id1, id2;
    std::cin >> id1 >> id2;
    if (id1 >= automates.size() || id2 >= automates.size()) {
        return;
    }

    switch (command) {
        case concat: {
            automates[id1].concat(automates[id2]);
            return;
        }
        case onion: {
            automates[id1].onion(automates[id2]);
            return;
        }
    }
}
