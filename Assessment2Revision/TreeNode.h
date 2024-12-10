#pragma once
#include <iostream>

template<typename T>
class TreeNode {
public:
    explicit TreeNode(T value = 0, TreeNode<T> *left = nullptr, TreeNode<T> *right = nullptr)
        : value(value), left(left), right(right) {}

    ~TreeNode() {
        delete left;
        delete right;
    }

    T getValue() const {
        return value;
    }

    TreeNode<T>*& getLeft() {
        return left;
    }

    TreeNode<T>*& getRight() {
        return right;
    }

    void setLeft(TreeNode<T>* left) {
        this->left = left;
    }

    void setRight(TreeNode<T>* right) {
        this->right = right;
    }

    void toString() const {
        if (this->left) {
            left->toString();
        }
        std::cout << this->getValue() << std::endl;
        if (this->right) {
            right->toString();
        }
    }

    int max() const {
        return max(0);
    }

    int max(int max) const {
        if (value > max) {
            max = value;
        }
        if (left) {
            max = left->max(max);
        }
        if (right) {
            max = right->max(max);
        }
        return max;
    }

    int sum() const {
        int total = value;
        if (left) {
            total += left->sum();
        }
        if (right) {
            total += right->sum();
        }
        return total;
    }

private:
    T value;
    TreeNode<T>* left = nullptr;
    TreeNode<T>* right = nullptr;
};