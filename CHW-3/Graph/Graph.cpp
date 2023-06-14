#pragma once
#include "vector"

class Graph {
private:
    int vertexes_amount_;
    int edges_amount_;
    std::vector<std::vector<int>> adjacency_matrix_;

public:
    Graph() = default;

    Graph(int n) {
        vertexes_amount_ = n;
        edges_amount_ = 0;
        adjacency_matrix_.resize(n, std::vector<int>(n, 0));
    }

    ~Graph() = default;

    void addEdge(int source, int destination, int weight) {
        adjacency_matrix_[source][destination] = weight;
        adjacency_matrix_[destination][source] = weight;
        edges_amount_++;
    }

    int getVertexesAmount() const {
        return vertexes_amount_;
    }

    int getEdgesAmount() const {
        return edges_amount_;
    }

    const std::vector<std::vector<int>>& getAdjacencyMatrix() const {
        return adjacency_matrix_;
    }
};