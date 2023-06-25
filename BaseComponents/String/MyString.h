#pragma once
#include <iostream>
#include<cstring>

//base is from Stoycho
class MyString
{
    char* _data;
    size_t _length;

    void copyFrom(const MyString& data);
    void free();

    explicit MyString(size_t capacity);
public:

    MyString();
    MyString(const char* data);
    MyString(char ch,int);
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    ~MyString();

    size_t length() const;
    MyString& operator+=(const MyString& other);
    MyString& operator+=(char ch);

    MyString substr(size_t begin, size_t howMany) const;

    char& operator[](size_t index);
    char operator[](size_t index) const;

    bool isEmpty() const;
    const char* c_str() const;
    void writeToFile(std::ofstream&ofs)const;
    void readFromFile(std::ifstream&ifs);
    friend MyString operator+(const MyString& lhs, const MyString& rhs);
    friend MyString operator+(char left, const MyString& rhs);
    friend MyString operator+(const MyString& lhs, char right);
    friend std::istream& operator>>(std::istream& is, MyString& str);
};

std::ostream& operator<<(std::ostream& os, const MyString& str);

bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);