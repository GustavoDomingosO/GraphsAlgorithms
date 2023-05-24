#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <set>

// Structure to represent an edge
struct Edge {
    int source;
    int destination;
    int weight;
};

// Function to generate a random number between min and max (inclusive)
int getRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// Function to generate a random graph with the specified number of vertices and edges
std::vector<Edge> generateRandomGraph(int numVertices, int numEdges) {
    std::vector<Edge> graph;
    std::set<std::pair<int, int>> edgeSet; // Set to check for duplicate edges

    while (graph.size() < numEdges) {
        Edge edge;
        edge.source = getRandomNumber(1, numVertices);
        edge.destination = getRandomNumber(1, numVertices);
        edge.weight = getRandomNumber(-5, 100); // Random weight between 1 and 100 (adjust as needed)

        // Check if the edge already exists in the graph
        if (edgeSet.find({edge.source, edge.destination}) == edgeSet.end()) {
            graph.push_back(edge);
            edgeSet.insert({edge.source, edge.destination});
        }
    }
    return graph;
}

int main() {
    int x = 20;
    while(true){
        int numVertices, numEdges;
        std::cout << "Enter the number of vertices: ";
        std::cin >> numVertices;
        if(numVertices == 999)break;
        std::cout << "Enter the number of edges: ";
        std::cin >> numEdges;

        std::vector<Edge> graph = generateRandomGraph(numVertices, numEdges);

        std::ofstream outputFile("teste" + std::to_string(x) + ".mtx");
        if (outputFile.is_open()) {
            outputFile << numVertices << " " << numEdges << std::endl;
            for (const auto& edge : graph) {
                outputFile << edge.source << " " << edge.destination << " " << edge.weight << std::endl;
            }
            outputFile.close();
            std::cout << "Output written to 'output.txt' file." << std::endl;
        } else {
            std::cerr << "Unable to open output file." << std::endl;
        }
        x++;
    }

    return 0;
}
