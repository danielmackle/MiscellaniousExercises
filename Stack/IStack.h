//
// Created by Daniel Mackle on 06/12/2024.
//

#pragma once;
class IStack {
public:
    virtual ~IStack() = default;
    virtual void* pop() = 0;
    [[nodiscard]] virtual void* peek() const = 0;
    virtual void remove();
    [[nodiscard]] virtual int getStackSize() const = 0;
    virtual void deleteStack() = 0;
    virtual void* peek();
    virtual void push(void*& input);
};
