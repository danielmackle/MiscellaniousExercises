#pragma once

template<typename T>
class Edge {
public:
    explicit Edge(const int indexFrom = 0, const int indexTo = 0, const int weight = 1)
        : indexFrom(indexFrom), indexTo(indexTo), weight(weight) {}

    ~Edge() = default;

    [[nodiscard]] int getIndexFrom() const {
        return indexFrom;
    }

    [[nodiscard]] int getIndexTo() const {
        return indexTo;
    }

    [[nodiscard]] int getWeight() const {
        return weight;
    }

    void setIndexFrom(const int indexFrom) {
        this->indexFrom = indexFrom;
    }

    void setIndexTo(const int indexTo) {
        this->indexTo = indexTo;
    }

    void setWeight(const int weight) {
        this->weight = weight;
    }

    void toString() const {
        std::cout << "From: " << indexFrom << ", To: " << indexTo << ", Weight: " << weight << std::endl;
    }

private:
    int indexFrom; // Starting vertex of the edge
    int indexTo;   // Ending vertex of the edge
    int weight;    // Weight of the edge
};