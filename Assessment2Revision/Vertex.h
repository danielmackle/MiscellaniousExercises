//
// Created by Daniel Mackle on 08/12/2024.
//

#pragma once
#include <iostream>

#include "Edge.h"

template<typename T>
class Vertex {
public:
    explicit Vertex(T value = 0, const int index = -1) : value(value), index(index) {
    }

    ~Vertex() {
    }

    void pushEdge(Edge<T> e) {
        edges->push_back(e);
    }

    Edge<T>* getEdge(int toIndex) const {
        for (Edge<T>& edge : *edges) {
            if (edge.getIndexTo() == toIndex) {
                return &edge;
            }
        }
        return nullptr;
    }

    std::vector<Edge<T> > *getEdges() const {
        return edges;
    }

    [[nodiscard]] int getIndex() const {
        return index;
    }

    [[nodiscard]] int getValue() const {
        return value;
    }

    void toString() {
        std::cout << "Vertex: " << index << std::endl << "Holds Edges:" << std::endl;
        for (Edge<T> e: *edges) {
            e.toString();
        }
    }

private:
    T value;
    int index;
    std::vector<Edge<T> > *edges = new std::vector<Edge<T> >();
};
