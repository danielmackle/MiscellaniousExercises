#include <vector>
#include "TreeNode.h"

int main();

// NOLINTNEXTLINE(bugprone-infinite-recursion)
void construct(const std::vector<int> &array);

// NOLINTNEXTLINE(bugprone-infinite-recursion)
void construct(const std::vector<int> &array, int first, int last);

// NOLINTNEXTLINE(bugprone-infinite-recursion)
template<typename T>
void construct(TreeNode<T> *&root, T value);

TreeNode<int> *root = nullptr;

int main() {
    const std::vector<int> array = {51, 5, 35, 23, 28, 60};
    construct(array);
    root->toString();
    std::cout<<std::endl<<"Max: "<<root->max()<<std::endl<<"Sum: " <<root->sum() << std::endl<<"Algorithms which traverse a built balanced BST have a time complexity of O(log(N)";
    delete root;
    return 0;
}

void construct(const std::vector<int> &array) {
    construct(array, 0, static_cast<int>(array.size() - 1));
}

void construct(const std::vector<int> &array, const int first, const int last) {// NOLINT(*-no-recursion)
    if (first > last) {
        return;
    }
    const int mid = first + (last - first) / 2;
    const int selected = array[mid];

    construct(root, selected);

    construct(array, first, mid - 1);
    construct(array, mid + 1, last);
}

template<typename T>
void construct(TreeNode<T> *&root, T value) { // NOLINT(*-no-recursion)
    if (!root) {
        root = new TreeNode<T>(value);
        return;
    }
    if (root->getValue() == value) {
        return;
    }
    if (value < root->getValue()) {
        TreeNode<T> *&left = root->getLeft();
        construct(left, value);
        return;
    }
    TreeNode<T> *&right = root->getRight();
    construct(right, value);
}
