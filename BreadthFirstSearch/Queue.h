//
// Created by Daniel Mackle on 09/12/2024.
//

#pragma once

#include "StackQueueNode.h"

template<typename T>
class Queue {
public:
    Queue() : firstNode(nullptr), lastNode(nullptr), size(0) {}

    ~Queue() {
        StackQueueNode<T> *currentNode = firstNode;
        while (currentNode != nullptr) {
            StackQueueNode<T> *nextNode = currentNode->getNext();
            delete currentNode;
            currentNode = nextNode;
        }
        firstNode = lastNode = nullptr; // Avoid dangling pointers
        size = 0;                       // Reset size to 0 for consistency
    }

    void enqueue(T value) {
        auto *newNode = new StackQueueNode<T>(value);
        if (!firstNode) {
            firstNode = newNode;
        }
        else {
            lastNode->setNext(newNode);
        }
        lastNode = newNode;
        size++;
    }

    [[nodiscard]] T dequeue() {
        StackQueueNode<T> holdData = *firstNode;
        delete firstNode;
        firstNode = holdData.getNext();
        size--;
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

    [[nodiscard]] T back() {
        return lastNode->getValue();
    }

    [[nodiscard]] bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

private:
    StackQueueNode<T> *firstNode;
    StackQueueNode<T> *lastNode;

    int size = 0;
};
