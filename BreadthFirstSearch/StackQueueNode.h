//
// Created by Daniel Mackle on 9/12/2024.
//

#pragma once

template<typename T>
class StackQueueNode {
public:
    explicit StackQueueNode(T value = 0, StackQueueNode<T> *next = nullptr) : value(value), next(next) {
    }

    ~StackQueueNode() = default;

    [[nodiscard]] T getValue() {
        return value;
    }

    void setValue(T value) {
        this->value = value;
    }

    [[nodiscard]] StackQueueNode *getNext() {
        return next;
    }

    void setNext(StackQueueNode *next) {
        this->next = next;
    }

private:
    T value;
    StackQueueNode *next;
};
