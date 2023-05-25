#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>

using namespace std;



void Prim(vector<vector<int>>& graph, int source, vector<int> &prev, vector<int> &cost, int numNodes, vector<pair<int, int>>& mstEdges)
{
    cost[source] = 0;
    //First element is the weight and the second is the vector
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push(make_pair(0, source));
    vector<bool> visited(numNodes, false);

    while(!minHeap.empty())
    {
        int currentNode = minHeap.top().second;
        minHeap.pop();

        visited[currentNode] = true;

        for (int i = 0; i < numNodes; i++) {

            if(graph[currentNode][i] != -1){

                int neighbor = i;
                int weight = graph[currentNode][i];

                if (!visited[neighbor] && weight < cost[neighbor]) {

                    cost[neighbor] = weight;
                    prev[neighbor] = currentNode;
                    
                    minHeap.push(make_pair(cost[neighbor], neighbor));

                    mstEdges.push_back(make_pair(currentNode, neighbor));
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
    cout << "-s\t\tMostra a solução" << endl;
}

int main(int argc, char* argv[]) {
    string outputFilename;
    string inputFilename;
    int initialVertex = 1;
    bool solution = false;

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
        } else if (arg == "-s"){
            solution = true;
        }
    }

    int numNodes, numEdges, u, v, cost;

    ifstream inputFile(inputFilename);

     if (!inputFile.is_open()) {
    cerr << "Erro: Falha ao abrir o arquivo de input" << endl;
    return 1;
    }
    //ifstream inputFile(inputFilename);

    inputFile >> numNodes >> numEdges;

    vector<vector<int>> graph(numNodes, vector<int>(numNodes, -1));

    for (int i = 0; i < numEdges; ++i) {
        inputFile >> u >> v >> cost;
        graph[u-1][v-1] = cost;
        graph[v-1][u-1] = cost;
    }
    inputFile.close();

    vector<int> prev(numNodes, -1);
    vector<int> cost_array(numNodes, INT_MAX);

    vector<pair<int, int>> mstEdges;

    Prim(graph, initialVertex - 1, prev, cost_array, numNodes, mstEdges);

    int finalcost = 0;

    for (int i = 0; i < numNodes; i++) {
      finalcost += cost_array[i];
    }
    
    sort(mstEdges.begin(), mstEdges.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
    });

    if(!outputFilename.empty())
    {
        ofstream outputFile(outputFilename);

        if (outputFile.is_open()) {
        streambuf* originalCoutBuffer = std::cout.rdbuf();  // Store the original cout buffer
        cout.rdbuf(outputFile.rdbuf());  

        if (solution) 
        {
            for (int i = 0; i < numNodes; i++) {
                if(prev[i] == -1) continue;
                cout << "(" << prev[i] + 1 << "," << i + 1  << ")";
                
                if (i != numNodes - 1) cout << " ";
                else cout << endl;
            }
        }
        else cout << finalcost << endl;

        std::cout.rdbuf(originalCoutBuffer);  // Restore the original cout buffer
        outputFile.close();
        }
    }    
    else {
        if (solution) 
        {
            for (int i = 0; i < numNodes; i++) {
                if(prev[i] == -1) continue;
                cout << "(" << prev[i] + 1 << "," << i + 1 << ")";
                
                if (i != numNodes - 1) cout << " ";
                else cout << endl;
            }
        }
        else cout << finalcost << endl;
    }
        
    return 0;
}