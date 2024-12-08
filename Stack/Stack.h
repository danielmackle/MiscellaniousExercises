//
// Created by Daniel Mackle on 05/12/2024.
//
#pragma once

#include "IStack.h"
#include "StackNode.h"

template<typename T>
class Stack final : IStack{
public:
    Stack() = default;

    ~Stack() override {
        Stack::deleteStack();
    }

    Stack(Stack &_stack) {
        auto *newStack = new Stack();
        newStack->stackSize = _stack.stackSize;
        StackNode currentStackNode = _stack->first;
        for (int i = 0; i < stackSize; i++) {
            newStack->push(currentStackNode);
            currentStackNode = currentStackNode->template getNext<T>();
        }
        this = newStack;
    }

    T pop() override {
        if (stackSize == 0) {
            return -1;
        }
        T hold = this->first->getValue();
        this->remove();
        return hold;
    }

    T peek() const override {
        if (stackSize == 0) {
            return -1;
        }
        return this->first->getValue();
    }

    void remove() override {
        const StackNode<T> *hold = first;
        stackSize--;
        first = first->getNext();
        delete hold;
    }

    void push(void* &_value) override{
        auto *newNode = new StackNode<T>(_value);
        StackNode<T> *hold = first;
        newNode->setNext(hold);
        first = newNode;
        stackSize++;
    }

    [[nodiscard]] int getStackSize() const override {
        return stackSize;
    }

    void deleteStack() override{
        StackNode<T> *currentNode = first;
        for (int i = 0; i < stackSize - 1; i++) {
            StackNode<T> hold = currentNode;
            delete currentNode;
            currentNode = hold->getNext();
        }
    }

private:
    StackNode<T> *first = nullptr;
    int stackSize = 0;
};
