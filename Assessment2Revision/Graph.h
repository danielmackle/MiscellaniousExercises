//
// Created by Daniel Mackle on 08/12/2024.
//

#pragma once
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <vector>
#include "Vertex.h"
#include "Queue.h"

template<typename T>
class Graph {
public:
    explicit Graph() = default;

    ~Graph() = default;

    void addVertex(int value) {
        auto newVertex = Vertex<T>(value, currentAddIndex++);
        arrayOfVertexes.push_back(newVertex);
    }

    void createEdge(int indexV1, int indexV2, int weight = 1) {
        Vertex<T> *v1 = &arrayOfVertexes[indexV1];
        Vertex<T> *v2 = &arrayOfVertexes[indexV2];
        Edge edge1to2 = Edge<int>(indexV2, weight);
        Edge edge2to1 = Edge<int>(indexV1, weight);
        v1->pushEdge(edge1to2);
        v2->pushEdge(edge2to1);
    }

    void getEdge(int indexV1, int indexV2) {
        Vertex<T> v1 = arrayOfVertexes[indexV1];
        Vertex<T> v2 = arrayOfVertexes[indexV2];
        auto *edge = arrayOfVertexes[v1.index].getEdge(v2.index);
    }

    void toString() {
        for (Vertex<T> v: arrayOfVertexes) {
            v.toString();
        }
    }

    void depthFirstSearch(T search) {
        auto visited = std::unordered_set<int>();
        auto backtrack = Queue<int>();
        T value = depthFirstSearch(search, 0, visited, backtrack);
        if (value == NULL) {
            std::cout << "Value not found: " << search << std::endl << std::endl;
            return;
        }
        std::cout << "Value found: " << search << std::endl << "Backtrack:" << std::endl;
        while (!backtrack.isEmpty()) {
            std::cout << "Node " << backtrack.dequeue() << std::endl;
        }
        std::cout << std::endl;
    }

    void breadthFirstSearch(T search) {
        auto visited = std::unordered_set<int>();
        auto backtrack = Queue<int>();
        Queue<int> queueIndexesToSearch;
        queueIndexesToSearch.enqueue(0);
        T value = breadthFirstSearch(search, queueIndexesToSearch, visited, backtrack);
        if (value == NULL) {
            std::cout << "Value not found: " << search << std::endl << std::endl;
            return;
        }
        std::cout << "Value found: " << search << std::endl << "Backtrack:" << std::endl;
        for (int i = 0; i < backtrack.getSize() - 1; i++) {
            std::cout << "Node " << backtrack.dequeue() << std::endl;
        }
        std::cout << std::endl;
    }

    void dijkstra(T search) {
        std::vector<int> minDistances(arrayOfVertexes.size(), INT_MAX), previousNode(arrayOfVertexes.size(), -1);
        std::unordered_set<int> visited;
        std::priority_queue<Edge<T>, std::vector<Edge<T> >, compareEdges> pq;
        Queue<int> backtrack;
        minDistances[0] = 0;
        pq.emplace(0, 0);
        int totalWeight = dijkstraHelper(search, pq, visited, minDistances, previousNode, backtrack);
        if (totalWeight == -1) {
            std::cout << "Node " << search << " not found!" << std::endl;
            return;
        }
        if (totalWeight == 0) {
            std::cout << "Weight from root node 0 to " << search << " is 0." << std::endl
                    << "No traversal is needed as " << search << " is the root node." << std::endl;
            return;
        }
        std::cout << "Weight from root node 0 to " << search << " is: " << totalWeight << std::endl << "Backtrack:" <<
                std::endl;
        while (!backtrack.isEmpty()) { std::cout << "Node " << backtrack.dequeue() << std::endl; }
    }

private:
    int currentAddIndex = 0;
    std::vector<Vertex<T> > arrayOfVertexes = std::vector<Vertex<T> >();

    T depthFirstSearch(T search, int currentIndex, std::unordered_set<T> &setSearchedIndexes, Queue<int> &backtrack) {
        setSearchedIndexes.insert(currentIndex);
        backtrack.enqueue(currentIndex);
        Vertex<T> currentVertex = arrayOfVertexes[currentIndex];
        if (currentVertex.getValue() == search) { return search; }
        for (Edge<T> pEdge: *currentVertex.getEdges()) {
            if (!setSearchedIndexes.contains(pEdge.getIndex())) {
                T result = depthFirstSearch(search, pEdge.getIndex(), setSearchedIndexes, backtrack);
                if (result != -1) {
                    return result;
                }
            }
        }
        backtrack.remove();
        return NULL;
    }

    T breadthFirstSearch(T search, Queue<int> &queueIndexesToSearch, std::unordered_set<int> &setSearchedIndexes,
                         Queue<int> &backtrack) {
        if (queueIndexesToSearch.isEmpty()) { return NULL; }
        int currentIndex = queueIndexesToSearch.dequeue();
        if (setSearchedIndexes.contains(currentIndex)) {
            return breadthFirstSearch(search, queueIndexesToSearch, setSearchedIndexes, backtrack);
        }
        setSearchedIndexes.insert(currentIndex);
        Vertex<T> currentVertex = arrayOfVertexes[currentIndex];
        if (currentVertex.getValue() == search) { return search; }
        for (Edge<T> pEdge: *currentVertex.getEdges()) {
            if (!setSearchedIndexes.contains(pEdge.getIndex())) {
                backtrack.enqueue(pEdge.getIndex());
                queueIndexesToSearch.enqueue(pEdge.getIndex());
            }
        }
        return breadthFirstSearch(search, queueIndexesToSearch, setSearchedIndexes, backtrack);
    }

    struct compareEdges {
        bool operator()(const Edge<T> &e1, const Edge<T> &e2) {
            return e1.getWeight() > e2.getWeight();
        }
    };

    int dijkstra(T search, std::priority_queue<Edge<int>, std::vector<Edge<int> >, compareEdges> &pq,
                 std::unordered_set<int> &visited, std::vector<int> &minDistances,
                 std::vector<int> &previousNode, Queue<int> &backtrack) {
        if (pq.empty()) return -1;
        Edge<T> currentEdge = pq.top();
        pq.pop();
        if (!visited.insert(currentEdge.getIndex()).second) return dijkstra(
            search, pq, visited, minDistances, previousNode, backtrack);
        Vertex<T> currentVertex = arrayOfVertexes[currentEdge.getIndex()];
        if (currentVertex.getValue() == search) {
            for (int backtrackNode = currentEdge.getIndex(); backtrackNode != -1;
                 backtrackNode = previousNode[backtrackNode])
                backtrack.enqueue(backtrackNode);
            return currentEdge.getWeight();
        }
        for (Edge<T> &edge: *currentVertex.getEdges()) {
            int newDist = currentEdge.getWeight() + edge.getWeight();
            if (newDist < minDistances[edge.getIndex()]) {
                minDistances[edge.getIndex()] = newDist;
                previousNode[edge.getIndex()] = currentEdge.getIndex();
                pq.emplace(edge.getIndex(), newDist);
            }
        }
        return dijkstra(search, pq, visited, minDistances, previousNode, backtrack);
    }
};
