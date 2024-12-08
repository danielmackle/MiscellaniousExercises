//
// Created by DanielMackle on 05/12/2024.
//

#pragma once

template <typename T>
class StackNode {
public:
    explicit StackNode(T _value=0, StackNode* _next=nullptr) : value(_value), next(_next) {}
    StackNode* getNext() const{
        return next;
    }
    void setNext(StackNode* _nextNode){
        this->next = _nextNode;
    }
    T getValue() const{
        return value;
    }
    void setValue(const T _input) {
        this->value = _input;
    }

private:
    T value;
    StackNode* next;
};
