#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

void Dijkstra(vector<vector<int>>& graph, int source, int dist[], int prev[], int numNodes) 
{
    dist[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    minHeap.push(make_pair(0, source));

    while(!minHeap.empty())
    {
        int currentNode = minHeap.top().second;
        minHeap.pop();

        for (int i = 0; i < numNodes; i++) {

            if(graph[currentNode][i] != -1){

                int neighbor = i;
                int weight = graph[currentNode][i];

                if (dist[currentNode] + weight < dist[neighbor]) {
                    dist[neighbor] = dist[currentNode] + weight;
                    minHeap.push(make_pair(dist[neighbor], neighbor));
                    prev[neighbor] = currentNode + 1;
                }

            }

        }
    }
} 




void printHelp() {
    cout << "-h\t\tMostra a ajuda" << endl;
    cout << "-o <arquivo>\tEspecifica o 'arquivo' de output" << endl;
    cout << "-f <arquivo>\tEspecifica o 'arquivo' de input" << endl;
    cout << "-i\t\tInidica o vértice inicial" << endl;
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
                cerr << "Erro: Faltando o argumento para '-o'" << endl;
                return 1;
            }
        } else if (arg == "-f") {
            if (i + 1 < argc) {
                inputFilename = argv[i + 1];
                ++i;
            } else {
                cerr << "Erro: Faltando o argumento para '-f'" << endl;
                return 1;
            }
        } else if (arg == "-i") {
            initialVertex = stoi(argv[i + 1]);
        }
    }

    int numNodes, numEdges, u, v, weight;

    ifstream inputFile(inputFilename);
 
    inputFile >> numNodes >> numEdges;

    vector<vector<int>> graph(numNodes, vector<int>(numNodes, -1));

    for (int i = 0; i < numEdges; ++i) {
        inputFile >> u >> v >> weight;
        graph[u-1][v-1] = weight;
        graph[v-1][u-1] = weight;
    }
    inputFile.close();


    int prev[numNodes];
    int dist[numNodes];

    for(int i = 0; i < numNodes; i++)
    {
        prev[i] = -1;
        dist[i] =  numeric_limits<int>::max();
    }

    Dijkstra(graph, initialVertex - 1, dist, prev,  numNodes);

    string result;

    if(!outputFilename.empty())
    {
        ofstream outputFile(outputFilename);
        if (outputFile.is_open()) {
        streambuf* originalCoutBuffer = std::cout.rdbuf();  // Store the original cout buffer
        cout.rdbuf(outputFile.rdbuf());  


        for(int i = 0; i < numNodes; i++)
        {
            if(dist[i] == numeric_limits<int>::max()) result = "-1";
            else result = to_string(dist[i]);
            cout << i + 1 << ":" << result;
            if(i < numNodes - 1)cout << " ";
        }

        std::cout.rdbuf(originalCoutBuffer);  // Restore the original cout buffer
        outputFile.close();
        }
    }    
    else {

        for(int i = 0; i < numNodes; i++)
        {
            if(dist[i] == numeric_limits<int>::max()) result = "-1";
            else result = to_string(dist[i]);
            cout << i + 1 << ":" << result;
            if(i < numNodes - 1)cout << " ";
        }
    }

    return 0;
}