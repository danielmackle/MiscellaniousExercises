#include <iostream>
#include <filesystem>

#include "Graph.h"
#include "Tree.h"
namespace fs = std::filesystem;

std::string createAndReturnFileAddress(const std::string& directory, const std::string& fileName) {
    if (!fs::exists(directory)) {
        fs::create_directory(directory);
    }
    const fs::path filePath = fs::path(directory) / fileName;

    if (const std::ofstream file(filePath, std::ios::app); !file) {
        std::cerr << "Error creating file: " << filePath << std::endl;
        return "";
    }

    return filePath.string();
}
template <typename T>
Graph<T> loadGraph() {
    const std::string directory = std::filesystem::current_path().string();
    const std::string fileName = "Save.txt";

    const std::string filePath = createAndReturnFileAddress(directory, fileName);

    if (filePath.empty()) {
        return NULL;
    }

    auto graph = Graph<int>(filePath);
}
int main() {
    std::vector array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Tree<int> tree = Tree<int>();
    tree.construct(array);
    tree.toString();
    return 0;
}
