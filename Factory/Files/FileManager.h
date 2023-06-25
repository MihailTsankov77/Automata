#pragma once

#include "../../Main/Automata.h"
#include "Factory/AutomataInterface.h"

class FileManager {
private:
    FileManager() = default;

    FileManager(const FileManager &) = delete;

    FileManager &operator=(const FileManager &) = delete;

public:
    static FileManager &getInstance();

    Automata readFromFile(const MyString &) const;

    void saveInFile(const MyString &, const Automata &) const;
};