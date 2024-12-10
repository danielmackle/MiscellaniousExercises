//
// Created by Daniel Mackle 8/12/2024.
//

#pragma once

template<typename T>
class Edge {
public:
    explicit Edge(const int index = 0, const int weight = 1) : index(index),
                                                               weight(weight) {
    }

    ~Edge() = default;

    [[nodiscard]] int getIndex() const {
        return index;
    }

    [[nodiscard]] int getWeight() const {
        return weight;
    }

    void setIndex(const int index) {
        this->index = index;
    }

    void setWeight(const int weight) {
        this->weight = weight;
    }

    void toString() {
        std::cout << "Index: " << index << std::endl << "Weight: " << weight << std::endl << std::endl;
    }

private:
    int index;
    int weight;
};
