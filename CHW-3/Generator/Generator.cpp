#pragma once
#include "random"
#include "../Graph/Graph.cpp"

class Generator {
public:
    static Graph generateCompleteGraph(int n) {
        Graph randomGraph(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int randomWeight = rand() % 50 + 1;
                randomGraph.addEdge(i, j, randomWeight);
            }
        }
        return randomGraph;
    }

    static Graph generateConnectedGraph(int n) {
        Graph randomGraph(n);
        std::random_device randomSeed;
        std::mt19937 generator(randomSeed());
        std::uniform_real_distribution<> possibilityGenerator(0.0, 1.0);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (possibilityGenerator(generator) <= 0.45) {
                    int randomWeight = rand() % 50 + 1;
                    randomGraph.addEdge(i, j, randomWeight);
                }
            }
        }
        return randomGraph;
    }

    static Graph generateSparseGraph(int n) {
        Graph randomGraph(n);
        for (int child = 1; child < n; ++child) {
            int randomWeight = rand() % 50 + 1;
            int randomParent = rand() % child;
            randomGraph.addEdge(randomParent, child, randomWeight);
        }
        return randomGraph;
    }
};