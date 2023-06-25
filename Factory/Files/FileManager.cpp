
#include "FileManager.h"
#include "fstream";

FileManager &FileManager::getInstance() {
    static FileManager factory;
    return factory;
}


Automata FileManager::readFromFile(const std::string &filePath) const {
    std::fstream file(filePath, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("FIX YOUR FILE, please, don't open");
    }

    int statesCount;
    file.read((char *) &statesCount, sizeof(statesCount));

    Automata toReturn(statesCount);

    for (int i = 0; i < statesCount; ++i) {
        State::Id id;
        int status;
        file.read((char *) &id, sizeof(State::Id));
        file.read((char *) &status, sizeof(status));

        toReturn.addState(id);

        if (status % 2 == 0) {
            toReturn.makeBegging(id);
        }

        if (status % 3 == 0) {
            toReturn.makeFinal(id);
        }
    }

    int commandsCount;
    file.read((char *) &commandsCount, sizeof(commandsCount));

    for (int i = 0; i < commandsCount; ++i) {
        State::Id id1, id2;
        char letter;
        file.read((char *) &id1, sizeof(State::Id));
        file.read(&letter, sizeof(char));
        file.read((char *) &id2, sizeof(State::Id));

        toReturn.addConnection(id1, letter, id2);
    }

    return toReturn;
}

void FileManager::saveInFile(const std::string &filePath, const Automata &toSave) const {
    std::fstream file(filePath, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("FIX YOUR FILE, please, don't open");
    }

    toSave.saveIds(file);
    toSave.saveConnections(file);

}

