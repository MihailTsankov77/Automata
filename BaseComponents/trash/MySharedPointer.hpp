#pragma once

#include "MyReferenceCounter.h"

template<class Type>
class MySharedPointer {
private:
    Type *ptr = nullptr;
    MyReferenceCounter counter;

public:
    MySharedPointer() = default;

    MySharedPointer(const MySharedPointer &);

    MySharedPointer &operator=(const MySharedPointer &);

    ~MySharedPointer();

private:
    void copyFrom(const MySharedPointer &);

    void free();

public:
    explicit MySharedPointer(Type *);

    void reset();

    const Type &operator*() const;

    Type &operator*();

    const Type *operator->() const;

    Type *operator->();

    bool operator!() const;

};

template<class Type>
MySharedPointer<Type>::MySharedPointer(const MySharedPointer &other) {
    copyFrom(other);
}

template<class Type>
MySharedPointer<Type> &MySharedPointer<Type>::operator=(const MySharedPointer &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

template<class Type>
MySharedPointer<Type>::~MySharedPointer() {
    free();
}

template<class Type>
void MySharedPointer<Type>::copyFrom(const MySharedPointer &other) {
    counter = other.counter;
    ptr = other.ptr;
}

template<class Type>
void MySharedPointer<Type>::free() {
    counter.decrement();
    if (counter.shouldDelete()) {
        delete ptr;
    }
}

template<class Type>
MySharedPointer<Type>::MySharedPointer(Type *value) {
    ptr = value;
    counter.increment();
}

template<class Type>
void MySharedPointer<Type>::reset() {
    ptr = nullptr;
//    *this = MySharedPointer();
}

template<class Type>
const Type &MySharedPointer<Type>::operator*() const {
    return *ptr;
}

template<class Type>
Type &MySharedPointer<Type>::operator*() {
    return *ptr;
}

template<class Type>
const Type *MySharedPointer<Type>::operator->() const {
    return ptr;
}

template<class Type>
Type *MySharedPointer<Type>::operator->() {
    return ptr;
}


template<class Type>
bool MySharedPointer<Type>::operator!() const {
    return ptr == nullptr;
}
