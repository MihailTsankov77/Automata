#pragma once

#include "../../Main/Automata.h"
#include "BaseComponents/String/MyString.h"

class RegExParser {
private:
    RegExParser() = default;

    RegExParser(const RegExParser &) = delete;

    RegExParser &operator=(const RegExParser &) = delete;

    bool isAlphabet(char) const;

    Automata createAutomata(MyString &regEx, bool hasOpenBracket = false) const;

public:
    static RegExParser &getInstance();

    Automata parse(const MyString &) const;

    void printRules() const;
};

