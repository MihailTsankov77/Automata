#pragma once

#include <iostream>

template<class Type>
class MySet {

    Type *data;
    size_t length = 0;
    size_t capacity = 8;


    void copyFrom(const MySet &other);

    void free();

    void resize();

public:
    MySet();

    explicit MySet(size_t n);

    MySet(const MySet &other);

    MySet &operator=(const MySet &other);

    ~MySet();

    bool contains(const Type &) const;

    Type &operator[](size_t n);

    const Type &operator[](size_t n) const;

    MySet &push(Type ch);

    void clear();

    size_t size() const;
};


template<typename Type>
void MySet<Type>::copyFrom(const MySet &other) {
    length = other.length;
    capacity = other.capacity;

    data = new Type[capacity];
    for (int i = 0; i < other.length; i++) {
        data[i] = other.data[i];
    }
}

template<typename Type>
void MySet<Type>::free() {
    length = 0;
    capacity = 0;
    delete[] data;
}

template<typename Type>
void MySet<Type>::resize() {
    capacity *= 2;

    Type *temp = new Type[capacity];

    for (int i = 0; i < length; i++) {
        temp[i] = data[i];
    }

    delete[] data;
    data = temp;
}

template<typename Type>
MySet<Type>::MySet():MySet(8) {}

template<typename Type>
MySet<Type>::MySet(size_t n) {
    capacity = n;
    length = 0;
    data = new Type[n];
}

template<typename Type>
MySet<Type>::MySet(const MySet<Type> &other) {
    copyFrom(other);
}

template<typename Type>
MySet<Type> &MySet<Type>::operator=(const MySet<Type> &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}


template<typename Type>
bool MySet<Type>::contains(const Type &el) const {
    for (int i = 0; i < length; i++) {
        if (data[i] == el) {
            return true;
        }
    }
    return false;
}

template<typename Type>
Type &MySet<Type>::operator[](size_t n) {
    return data[n];
}


template<typename Type>
const Type &MySet<Type>::operator[](size_t n) const {
    return data[n];
}

template<typename Type>
size_t MySet<Type>::size() const {
    return length;
}


template<typename Type>
MySet<Type> &MySet<Type>::push(Type ch) {
    if (length == capacity) {
        resize();
    }
    for (int i = 0; i < length; i++) {
        if (data[i] == ch) {
            return *this;
        }
    }

    data[length] = ch;
    length++;
    return *this;
}

template<typename Type>
void MySet<Type>::clear() {
    free();
    capacity = 5;
    data = new Type[capacity];
}

template<typename Type>
MySet<Type>::~MySet() {
    free();
}
