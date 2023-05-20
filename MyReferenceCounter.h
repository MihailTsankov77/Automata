#pragma once

#include <cstddef>

class MyReferenceCounter {
private:
    size_t *count = nullptr;

public:
    MyReferenceCounter();

    MyReferenceCounter(const MyReferenceCounter &);

    MyReferenceCounter &operator=(const MyReferenceCounter &);

    // TODO move???
    ~MyReferenceCounter();

private:
    void copyFrom(const MyReferenceCounter &);

    void free();

public:
    void increment() const;

    void decrement() const;

    bool shouldDelete() const;
};