//
// Created by Daniel Mackle on 09/12/2024.
//

#pragma once

#include "StackQueueNode.h"

template<typename T>
class Stack {
public:
    Stack() : firstNode(nullptr), size(0) {
    }

    ~Stack() {
        StackQueueNode<T> *currentNode = firstNode;
        while (currentNode != nullptr) {
            StackQueueNode<T> *nextNode = currentNode->getNext();
            delete currentNode;
            currentNode = nextNode;
        }
        firstNode = nullptr;
        size = 0;
    }

    void push(T value) {
        auto *newNode = new StackQueueNode<T>(value);
        if (firstNode) {
            newNode->setNext(firstNode);
        }
        firstNode = newNode;
        size++;
    }

    [[nodiscard]] T pop() {
        StackQueueNode<T> holdData = *firstNode;
        delete firstNode;
        size--;
        firstNode = holdData.getNext();
        return holdData.getValue();
    }

    void remove() {
        StackQueueNode<T> holdData = *firstNode;
        delete firstNode;
        size--;
        firstNode = holdData.getNext();
    }

    [[nodiscard]] T front() {
        return firstNode->getValue();
    }

    [[nodiscard]] bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

private:
    StackQueueNode<T> *firstNode;

    int size = 0;
};
