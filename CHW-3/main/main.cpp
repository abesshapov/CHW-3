#include "iostream"
#include "chrono"
#include "fstream"
#include "functional"
#include "vector"
#include "../Generator/Generator.cpp"
#include "../Algorithms/Algorithms.cpp"
#include "../Graph/Graph.cpp"

std::fstream file("measures.csv", std::ios::out | std::ios::app);

void outputMeasurements(
    const Graph& graph,
    const std::function<std::vector<int>(const Graph&, int)>& algorithm) {
    long long total_time = 0.0;
    for (int i = 0; i < 1; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> res = algorithm(graph, 0);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        total_time += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    }
    auto average_elapsed_time = total_time / 10.0;
    file << average_elapsed_time << ";";
    std::cout << "Time: " << average_elapsed_time << " ns";
    std::cout << std::endl;
}

int main() {
    std::vector<std::string> graphs_names = {
        "Complete graph",
        "Connected graph",
        "Sparse graph"
    };
    std::vector<std::string> algorithms_names = {
            "Dijkstra algorithm\n",
            "Floyd-Warshall algorithm\n",
            "Bellman-Ford algorithm\n"
    };
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    file << ";";
    std::vector<bool> graphs_written(3);
    for (int vertexes_amount = 10; vertexes_amount <= 1010; vertexes_amount += 50) {
        file << "Dijkstra;FloydWarshall;BellmanFord;";
    }
    file << "\n;";
    for (int vertexes_amount = 10; vertexes_amount <= 1010; vertexes_amount += 50) {
        std::vector<Graph> graphs = {
                Generator::generateCompleteGraph(vertexes_amount),
                Generator::generateConnectedGraph(vertexes_amount),
                Generator::generateSparseGraph(vertexes_amount)
        };
        file << graphs[0].getVertexesAmount() << " vertexes / " << graphs[0].getEdgesAmount() << " edges;;;";
    }
    file << "\n";
    for (int i = 0; i < 3; ++i) {
        for (int vertexes_amount = 10; vertexes_amount <= 1010; vertexes_amount += 50) {
            std::vector<Graph> graphs = {
                    Generator::generateCompleteGraph(vertexes_amount),
                    Generator::generateConnectedGraph(vertexes_amount),
                    Generator::generateSparseGraph(vertexes_amount)
            };
            std::cout << "[" << graphs[0].getVertexesAmount() << " vertices, " << graphs[0].getEdgesAmount()
                << " edges]\n";
            std::cout << graphs_names[i] << "\n";
            std::vector<std::function<std::vector<int>(const Graph&, int)>> algorithms = {
                    Algorithms::Dijkstra,
                    Algorithms::FloydWarshall,
                    Algorithms::BellmanFord
            };
            if (!graphs_written[i]) {
                file << graphs_names[i] << ";";
                graphs_written[i] = true;
            }
            for (int j = 0; j < 3; ++j) {
                std::cout << algorithms_names[j];
                outputMeasurements(graphs[i], algorithms[j]);
            }
            std::cout << "\n";
        }
        file << "\n";
    }
    file.close();
}