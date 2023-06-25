#pragma once

#include "../../Main/Automata.h"

class FileManager {
private:
    FileManager() = default;

    FileManager(const FileManager &) = delete;

    FileManager &operator=(const FileManager &) = delete;

public:
    static FileManager &getInstance();

    Automata readFromFile(const std::string &) const;

    void saveInFile(const std::string &, const Automata &) const;
};