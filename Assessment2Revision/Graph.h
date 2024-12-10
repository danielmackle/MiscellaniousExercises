//
// Created by Daniel Mackle on 08/12/2024.
//

#pragma once
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <vector>
#include <fstream>
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

    explicit Graph(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return;
        }
        arrayOfVertexes.clear();
        int numOfVertices, indexTo, indexFrom, weight;
        file >> numOfVertices;
        file >> undirectedDirected;

        for (int i = 0; i < numOfVertices; i++) {
            int value = 0;
            file >> value;
            Vertex<T> newVertex(value, i);
            arrayOfVertexes.push_back(newVertex);
        }

        while (file >> indexFrom >> indexTo >> weight) {
            createEdge(indexFrom, indexTo, weight);
        }
        file.close();
    }

    struct pair_hash {
        template <typename T1, typename T2>
        std::size_t operator+(const std::pair<T1, T2>& p) const {
            auto h1 = std::hash<T1>{}(p.first);
            auto h2 = std::hash<T2>{}(p.second);
            return h1 ^ (h2 << 1); // Combine the two hash values
        }
    };

    void save(const std::string& fileName) {
        std::ofstream file(fileName);
        if (!file) {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return;
        }

        file << arrayOfVertexes.size() << std::endl;
        file << undirectedDirected << std::endl;

        for (const Vertex<T>& vertex : arrayOfVertexes) {
            file << vertex.getValue() << std::endl;
        }

        std::unordered_set<std::pair<int, int>, pair_hash> setOfEdges{};
        for (const Vertex<T> &vertex: arrayOfVertexes) {
            for (const Edge<T> &edge: *vertex.getEdges()) {
                int from = edge.getIndexFrom();
                int to = edge.getIndexTo();

                if (undirectedDirected == 'u' && from > to) {
                    std::swap(from, to); // Normalize edge for undirected graph
                }

                setOfEdges.emplace(from, to);
            }
        }
        for (const auto &edge: setOfEdges) {
            file << edge.first << " " << edge.second << " "
                    << arrayOfVertexes[edge.first].getEdge(edge.second)->getWeight() << std::endl;
        }
        file.close();
    }

    void createEdge(int indexV1, int indexV2, int weight = 1) {
        Edge<T> edge1to2(indexV1, indexV2, weight);
        arrayOfVertexes[indexV1].pushEdge(edge1to2);
        if (undirectedDirected == 'u') {
            Edge<T> edge2to1(indexV2, indexV1, weight);
            arrayOfVertexes[indexV2].pushEdge(edge2to1);
        }
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
        int totalWeight = dijkstra(search, pq, visited, minDistances, previousNode, backtrack);
        if (totalWeight == -1) {
            std::cout << "Node " << search << " not found!" << std::endl;
            return;
        }
        if (totalWeight == 0) {
            std::cout << "Weight from root node 0 to node wth the value of " << search << " is 0." << std::endl
                    << "No traversal is needed as " << search << " is the root node." << std::endl;
            return;
        }
        std::cout << "Weight from root node 0 to node wth the value of " << search << " is: " << totalWeight << std::endl << "Backtrack:" <<
                std::endl;
        while (!backtrack.isEmpty()) { std::cout << "Node " << backtrack.dequeue() << std::endl; }
    }

private:
    char undirectedDirected = 'u';
    int currentAddIndex = 0;
    std::vector<Vertex<T> > arrayOfVertexes = std::vector<Vertex<T> >();

    T depthFirstSearch(T search, int currentIndex, std::unordered_set<T> &setSearchedIndexes, Queue<int> &backtrack) {
        setSearchedIndexes.insert(currentIndex);
        backtrack.enqueue(currentIndex);
        Vertex<T> currentVertex = arrayOfVertexes[currentIndex];
        if (currentVertex.getValue() == search) { return search; }
        for (Edge<T> pEdge: *currentVertex.getEdges()) {
            if (!setSearchedIndexes.contains(pEdge.getIndexTo())) {
                T result = depthFirstSearch(search, pEdge.getIndexTo(), setSearchedIndexes, backtrack);
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
            if (!setSearchedIndexes.contains(pEdge.getIndexTo())) {
                backtrack.enqueue(pEdge.getIndexTo());
                queueIndexesToSearch.enqueue(pEdge.getIndexTo());
            }
        }
        return breadthFirstSearch(search, queueIndexesToSearch, setSearchedIndexes, backtrack);
    }

    struct compareEdges {
        bool operator()(const Edge<T> &e1, const Edge<T> &e2) {
            return e1.getWeight() > e2.getWeight();
        }
    };

    int dijkstra(T search, std::priority_queue<Edge<int>, std::vector<Edge<int>>, compareEdges> &pq,
             std::unordered_set<int> &visited, std::vector<int> &minDistances,
             std::vector<int> &previousNode, Queue<int> &backtrack) {

        if (pq.empty()) return -1; // If the priority queue is empty, return -1

        Edge<T> currentEdge = pq.top();
        pq.pop();

        // If the node has already been visited, continue with the next node
        if (!visited.insert(currentEdge.getIndexTo()).second)
            return dijkstra(search, pq, visited, minDistances, previousNode, backtrack);

        Vertex<T> currentVertex = arrayOfVertexes[currentEdge.getIndexTo()];

        // If the current vertex value matches the search value, backtrack
        if (currentVertex.getValue() == search) {
            for (int backtrackNode = currentEdge.getIndexTo(); backtrackNode != -1;
                 backtrackNode = previousNode[backtrackNode])
                backtrack.enqueue(backtrackNode);
            return currentEdge.getWeight(); // Return the weight of the edge at the destination
        }

        // Update the distances for each adjacent edge
        for (Edge<T> &edge: *currentVertex.getEdges()) {
            int newDist = currentEdge.getWeight() + edge.getWeight();
            if (newDist < minDistances[edge.getIndexTo()]) {
                minDistances[edge.getIndexTo()] = newDist;
                previousNode[edge.getIndexTo()] = currentEdge.getIndexTo();
                pq.emplace(edge.getIndexFrom(),edge.getIndexTo(), newDist);
            }
        }

        // Continue the recursion
        return dijkstra(search, pq, visited, minDistances, previousNode, backtrack);
    }

};
