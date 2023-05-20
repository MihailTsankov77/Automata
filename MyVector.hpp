#pragma once

#include <cstddef>
#include <exception>
#include <stdexcept>

template<class Type>
class MyVector {
    Type *arr;
    size_t length = 0;
    size_t capacity = 0;

public:
    MyVector() noexcept;

private:
    static const size_t defaultCapacity = 8;

public:
    MyVector(const MyVector<Type> &) noexcept;

    MyVector(MyVector<Type> &&) noexcept;

    MyVector<Type> &operator=(const MyVector &) noexcept;

    MyVector<Type> &operator=(MyVector &&) noexcept;

    ~MyVector();

private:
    void copyFrom(const MyVector &) noexcept;

    void moveFrom(MyVector &&) noexcept;

    void free() noexcept;

public:
    explicit MyVector(size_t) noexcept;

    virtual void push(Type&&) noexcept;
    virtual void push(Type&) noexcept;

    const Type &peek(size_t) const;

    virtual void pop();

private:
    static const size_t resizeValue = 2;
    static const size_t maxResizeThreshold = 4;

    void resize(size_t) noexcept;

public:
    const Type &operator[](size_t) const;

    Type &operator[](size_t);

    bool isEmpty() const noexcept;

    size_t size() const noexcept;

private:
    void assertInBounds(size_t) const;
};

template<class Type>
MyVector<Type>::MyVector() noexcept:MyVector(defaultCapacity) {}

template<class Type>
MyVector<Type>::MyVector(const MyVector<Type> &other) noexcept {
    copyFrom(other);
}

template<class Type>
MyVector<Type>::MyVector(MyVector<Type> &&other) noexcept {
    moveFrom(std::move(other));
}

template<class Type>
MyVector<Type> &MyVector<Type>::operator=(const MyVector &other) noexcept {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

template<class Type>
MyVector<Type> &MyVector<Type>::operator=(MyVector &&other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

template<class Type>
MyVector<Type>::~MyVector() {
    free();
}

template<class Type>
void MyVector<Type>::copyFrom(const MyVector &other) noexcept {
    arr = new Type [other.capacity];
    for (int i = 0; i < other.size(); ++i) {
        arr[i] = other.arr[i];
    }

    length = other.length;
    capacity = other.capacity;
}

template<class Type>
void MyVector<Type>::moveFrom(MyVector &&other) noexcept {
    arr = other.arr;
    length = other.length;
    capacity = other.capacity;

    other.arr = nullptr;
    other.length = 0;
    other.capacity = 0;
}

template<class Type>
void MyVector<Type>::free() noexcept {
    delete[] arr;
}

template<class Type>
MyVector<Type>::MyVector(size_t capacity) noexcept:capacity(capacity) {
    arr = new Type[capacity];
}

template<class Type>
void MyVector<Type>::push(Type&& element) noexcept {
    if (size() >= capacity) {
        resize(capacity * resizeValue);
    }

    arr[length++] = element;
}

template<class Type>
void MyVector<Type>::push(Type & element) noexcept {
    if (size() >= capacity) {
        resize(capacity * resizeValue);
    }

    arr[length++] = element;
}


template<class Type>
const Type &MyVector<Type>::peek(size_t index) const {
    assertInBounds(index);

    return arr[index];
}

template<class Type>
void MyVector<Type>::pop() {
    if (isEmpty()) {
        throw std::range_error("Empty vector");
    }

    --length;

    if (size() * maxResizeThreshold <= capacity && !isEmpty()) {
        resize(capacity / resizeValue);
    }
}

template<class Type>
void MyVector<Type>::resize(size_t newCapacity) noexcept {
    Type *newArr = new Type[5];

    for (int i = 0; i < size(); ++i) {
        newArr[i] = arr[i];
    }

    delete[] arr;
    arr = newArr;

    capacity = newCapacity;
}

template<class Type>
const Type &MyVector<Type>::operator[](size_t index) const {
    assertInBounds(index);
    return arr[index];
}

template<class Type>
Type &MyVector<Type>::operator[](size_t index) {
    assertInBounds(index);
    return arr[index];
}

template<class Type>
bool MyVector<Type>::isEmpty() const noexcept {
    return size() == 0;
}

template<class Type>
size_t MyVector<Type>::size() const noexcept {
    return length;
}

template<class Type>
void MyVector<Type>::assertInBounds(size_t num) const{
    if (num >= size()) {
        throw std::range_error("Vector outside of bounds");
    }
}