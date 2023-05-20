#pragma once

template<class Key, class Value>
class MyPair {
private:
    Key key;
    Value value;

public:
    MyPair() = default;
    MyPair(const Key&, const Value&) noexcept;

    void setKey(const Key&) noexcept;
    const Key& getKey() const noexcept;
    bool isThisKey(const Key&) const noexcept;

    void setValue(const Value&) noexcept;
    const Value& getValue() const noexcept;
    Value& getValue() noexcept;
};

template<class Key, class Value>
MyPair<Key, Value>::MyPair(const Key & key, const Value & value)noexcept {
    setKey(key);
    setValue(value);
}

template<class Key, class Value>
void MyPair<Key, Value>::setKey(const Key & key) noexcept {
    this->key = key;
}

template<class Key, class Value>
const Key &MyPair<Key, Value>::getKey() const noexcept{
    return key;
}

template<class Key, class Value>
bool MyPair<Key, Value>::isThisKey(const Key& key) const noexcept {
    return this->key==key;
}

template<class Key, class Value>
void MyPair<Key, Value>::setValue(const Value & value) noexcept{
    this->value = value;
}

template<class Key, class Value>
const Value &MyPair<Key, Value>::getValue() const noexcept{
    return value;
}

template<class Key, class Value>
Value &MyPair<Key, Value>::getValue() noexcept{
    return value;
}
