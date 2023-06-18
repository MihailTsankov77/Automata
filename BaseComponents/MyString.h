#pragma once

#include <iostream>
#include<cstring>

class MyString {
    char *_data;
    size_t _length;

    void copyFrom(const MyString &data);

    void free();

    explicit MyString(size_t capacity, int);

public:

    MyString();

    MyString(const char *data);

    MyString(char ch);

    MyString(const MyString &other);

    MyString &operator=(const MyString &other);

    ~MyString();

    size_t length() const;

    bool empty() const;

    MyString &operator+=(const MyString &other);

    MyString &operator+=(char ch);

    MyString substr(size_t begin, size_t howMany) const;

    void erase(size_t begin, size_t howMany);

    char &operator[](size_t index);

    char operator[](size_t index) const;

    const char *c_str() const;

    friend MyString operator+(const MyString &lhs, const MyString &rhs);

    friend std::istream &operator>>(std::istream &is, MyString &str);
};

std::ostream &operator<<(std::ostream &os, const MyString &str);
