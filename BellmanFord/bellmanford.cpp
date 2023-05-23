#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

struct Edge {
    int source, destination, weight;
};

void bellmanFord(vector<Edge>& edges, int numVertices, int numEdges, int source, vector<int>& distances) {

    distances[source] = 0;

    for (int i = 0; i < numVertices - 1; ++i) {
        for (int j = 0; j < numEdges; ++j) {
            int u = edges[j].source;
            int v = edges[j].destination;
            int weight = edges[j].weight;
            //if(u == source)  cout << "distances[u] + weight < distances[v]: " << distances[u] << " + " << weight << " < " << distances[v] << endl;

            if (distances[u] != numeric_limits<int>::max() && distances[u] + weight < distances[v]) {

                distances[v] = distances[u] + weight;

             //   cout << "New distance of " << v << ": " << distances[v] << endl;
            }
            if (distances[v] != std::numeric_limits<int>::max() &&
                distances[v] + weight < distances[u]) {
                distances[u] = distances[v] + weight;
            }
        }
    }

    for (const auto& edge : edges) {
        int u = edge.source;
        int v = edge.destination;
        int weight = edge.weight;

        if (distances[u] != numeric_limits<int>::max() &&
            distances[u] + weight < distances[v]) {
            cout << "Graph contains negative-weight cycle.\n";
            return;
        }
    }
}

void printHelp() {
    cout << "-h\t\tShow help" << endl;
    cout << "-o <arquivo>\tRedirect output to 'arquivo'" << endl;
    cout << "-f <arquivo>\tSpecify the input graph 'arquivo'" << endl;
    cout << "-i\t\tSpecify the initial vertex" << endl;
}

int main(int argc, char* argv[]) {
    string outputFilename;
    string inputFilename;
    int initialVertex = 1;

    // Process command-line arguments
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-h") {
            printHelp();
            return 0;
        } else if (arg == "-o") {
            if (i + 1 < argc) {
                outputFilename = argv[i + 1];
                ++i;
            } else {
                cerr << "Error: Missing argument for '-o'" << endl;
                return 1;
            }
        } else if (arg == "-f") {
            if (i + 1 < argc) {
                inputFilename = argv[i + 1];
                ++i;
            } else {
                cerr << "Error: Missing argument for '-f'" << endl;
                return 1;
            }
        } else if (arg == "-i") {
            initialVertex = stoi(argv[i + 1]);
        }
    }

    int numNodes, numEdges, u, v, weight;

    ifstream inputFile(inputFilename);
 
    inputFile >> numNodes >> numEdges;

    vector<Edge> edges(numEdges);

    for (int i = 0; i < numEdges; ++i) {
        inputFile >> u >> v >> weight;
        edges[i].source = u - 1;
        edges[i].destination = v - 1;
        edges[i].weight = weight;
    }

    inputFile.close();
/*
    for (int i = 0; i < numEdges; ++i) {
        if (edges[i].source == 3) cout << "Testes :" << edges[i].source << " " << edges[i].destination << " " << edges[i].weight << endl;
    }*/
    
    vector<int> distances(numNodes, numeric_limits<int>::max());

    bellmanFord(edges, numNodes, numEdges, initialVertex - 1, distances);

    if(!outputFilename.empty())
    {
        ofstream outputFile(outputFilename);
        if (outputFile.is_open()) {
        streambuf* originalCoutBuffer = std::cout.rdbuf();  // Store the original cout buffer
        cout.rdbuf(outputFile.rdbuf());  


        for(int i = 0; i < numNodes; i++)
        {
            cout << i + 1 << ":" << distances[i];
            if(i < numNodes - 1)cout << " ";
        }

        std::cout.rdbuf(originalCoutBuffer);  // Restore the original cout buffer
        outputFile.close();
        }
    }    
    else {

        for(int i = 0; i < numNodes; i++)
        {
            cout << i + 1 << ":" << distances[i];
            if(i < numNodes - 1)cout << " ";
        }
    }

    return 0;
}