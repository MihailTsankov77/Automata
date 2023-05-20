
#include "MyReferenceCounter.h"

MyReferenceCounter::MyReferenceCounter() {
    count = new size_t;
    *count = 0;
}

MyReferenceCounter::MyReferenceCounter(const MyReferenceCounter &other) {
    copyFrom(other);
}


MyReferenceCounter &
MyReferenceCounter::operator=(const MyReferenceCounter &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}



MyReferenceCounter::~MyReferenceCounter() {
    free();
}


void MyReferenceCounter::copyFrom(const MyReferenceCounter &other) {
    count = other.count;
    increment();
}


void MyReferenceCounter::free() {
    if (shouldDelete()) {
        delete count;
    }
}


void MyReferenceCounter::increment() const {
    ++(*count);
}


void MyReferenceCounter::decrement() const {
    --(*count);
}


bool MyReferenceCounter::shouldDelete() const {
    return (*count) == 0;
}
