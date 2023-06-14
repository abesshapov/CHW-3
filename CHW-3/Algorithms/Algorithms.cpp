#pragma once
// Inspired by: https://prog-cpp.ru/deikstra/; https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/; 
// https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/.
#include "vector"
#include "climits"
#include "../Graph/Graph.cpp"

class Algorithms {
public:
    static std::vector<int> Dijkstra(const Graph& graph, int source) {
        int vertexes_amount = graph.getVertexesAmount();
        const std::vector<std::vector<int>>& adjacency_matrix = graph.getAdjacencyMatrix();
        std::vector<int> shortestDistances(vertexes_amount, INT_MAX);
        std::vector<bool> isVertexVisitted(vertexes_amount, false);
        shortestDistances[source] = 0;
        for (int i = 0; i < vertexes_amount - 1; ++i) {
            int shortest_distance = INT_MAX;
            int shortest_distance_index = 0;
            for (int j = 0; j < vertexes_amount; ++j) {
                if (!isVertexVisitted[j] && shortestDistances[j] <= shortest_distance) {
                    shortest_distance = shortestDistances[j];
                    shortest_distance_index = j;
                }
            }
            isVertexVisitted[shortest_distance_index] = true;
            for (int j = 0; j < vertexes_amount; ++j) {
                if (!isVertexVisitted[j] &&
                    adjacency_matrix[shortest_distance_index][j] &&
                    shortestDistances[shortest_distance_index] != INT_MAX &&
                    shortestDistances[shortest_distance_index] + adjacency_matrix[shortest_distance_index][j] < shortestDistances[j]) {
                    shortestDistances[j] = shortestDistances[shortest_distance_index] +
                        adjacency_matrix[shortest_distance_index][j];
                }
            }
        }
        return shortestDistances;
    }

    static std::vector<int> FloydWarshall(const Graph& graph, int source) {
        int vertexes_amount = graph.getVertexesAmount();
        const std::vector<std::vector<int>>& adjacency_matrix = graph.getAdjacencyMatrix();
        std::vector<int> shortestDistances(vertexes_amount, INT_MAX);
        shortestDistances[source] = 0;
        for (int i = 0; i < vertexes_amount; ++i) {
            for (int j = 0; j < vertexes_amount; ++j) {
                for (int z = 0; z < vertexes_amount; ++z) {
                    if (shortestDistances[j] != INT_MAX &&
                        adjacency_matrix[j][z] != INT_MAX &&
                        shortestDistances[j] + adjacency_matrix[j][z] < shortestDistances[z]) {
                        shortestDistances[z] = shortestDistances[j] + adjacency_matrix[j][z];
                    }
                }
            }
        }
        return shortestDistances;
    }

    static std::vector<int> BellmanFord(const Graph& graph, int source) {
        int vertexes_amount = graph.getVertexesAmount();
        const std::vector<std::vector<int>>& adjacency_matrix = graph.getAdjacencyMatrix();
        std::vector<int> shortestDistances(vertexes_amount, INT_MAX);
        shortestDistances[source] = 0;
        for (int i = 0; i < vertexes_amount - 1; ++i) {
            for (int j = 0; j < vertexes_amount; ++j) {
                for (int z = 0; z < vertexes_amount; ++z) {
                    if (adjacency_matrix[j][z] != 0 &&
                        shortestDistances[j] != INT_MAX &&
                        shortestDistances[j] + adjacency_matrix[j][z] < shortestDistances[z]) {
                        shortestDistances[z] = shortestDistances[j] + adjacency_matrix[j][z];
                    }
                }
            }
        }
        for (int i = 0; i < vertexes_amount; ++i) {
            for (int j = 0; j < vertexes_amount; ++j) {
                if (adjacency_matrix[i][j] != 0 &&
                    shortestDistances[i] != INT_MAX &&
                    shortestDistances[i] + adjacency_matrix[i][j] < shortestDistances[j]) {
                    return {};
                }
            }
        }
        return shortestDistances;
    }
};