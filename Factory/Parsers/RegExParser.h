#pragma once

#include "../../Main/Automata.h"

class RegExParser {
private:
    RegExParser() = default;

    RegExParser(const RegExParser &) = delete;

    RegExParser &operator=(const RegExParser &) = delete;

    bool isAlphabet(char) const;

    Automata createAutomata(std::string &regEx, bool hasOpenBracket = false) const;

public:
    static RegExParser &getInstance();

    Automata parse(const std::string &) const;

    void printRules() const;
};

