//
// Created by Daniel Mackle on 10/12/2024.
//

#pragma once
#include <vector>
#include "TreeNode.h"

template<typename T>
class Tree {
public:
    Tree() : root(nullptr) {}

    ~Tree() {
        delete root;
    }

    void construct(const std::vector<T>& array) {
        construct(array, 0, static_cast<int>(array.size() - 1));
    }

    void toString() const {
        if (root) {
            root->toString();
        }
    }

    int max() const {
        if (root) {
            return root->max();
        }
        return 0; // Or some default if the tree is empty
    }

    int sum() const {
        if (root) {
            return root->sum();
        }
        return 0; // Or some default if the tree is empty
    }

private:
    TreeNode<T>* root;

    void construct(const std::vector<T>& array, int first, int last) {
        if (first > last) {
            return;
        }
        int mid = first + (last - first) / 2;
        insert(array[mid]);
        construct(array, first, mid - 1);
        construct(array, mid + 1, last);
    }

    void insert(T value) {
        insert(root, value);
    }

    void insert(TreeNode<T>*& node, T value) {
        if (!node) {
            node = new TreeNode<T>(value);
            return;
        }
        if (value < node->getValue()) {
            insert(node->getLeft(), value);
        } else if (value > node->getValue()) {
            insert(node->getRight(), value);
        }
    }
};
