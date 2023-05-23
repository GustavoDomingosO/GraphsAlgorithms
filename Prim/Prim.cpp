#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;

//Prim - Minimum spanning tree

void Prim(vector<vector<int>>& graph, int source, int prev[], int cost[], int numNodes)
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
                }
            }
        }
    }
}

void printHelp() {
    cout << "-h\t\tShow help" << endl;
    cout << "-o <arquivo>\tRedirect output to 'arquivo'" << endl;
    cout << "-f <arquivo>\tSpecify the input graph 'arquivo'" << endl;
    cout << "-i\t\tSpecify the initial vertex" << endl;
    cout << "-s\t\tShow solution" << endl;
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
        } else if (arg == "-s"){
            solution = true;
        }
    }

    int numNodes, numEdges, u, v, cost;

    ifstream inputFile(inputFilename);
 
    inputFile >> numNodes >> numEdges;


    vector<vector<int>> graph(numNodes, vector<int>(numNodes, -1));

    for (int i = 0; i < numEdges; ++i) {
        inputFile >> u >> v >> cost;
        graph[u-1][v-1] = cost;
        graph[v-1][u-1] = cost;
    }
    inputFile.close();

    int prev[numNodes];
    int cost_array[numNodes];

    for(int i = 0; i < numNodes; i++)
    {
        prev[i] = -1;
        cost_array[i] =  INT_MAX;
    }

    Prim(graph, initialVertex - 1, prev, cost_array, numNodes);

    int finalcost = 0;

    for (int i = 0; i < numNodes; i++) {
      finalcost += cost_array[i];
    }

    if(!outputFilename.empty())
    {
        ofstream outputFile("output.txt");

        if (outputFile.is_open()) {
        streambuf* originalCoutBuffer = std::cout.rdbuf();  // Store the original cout buffer
        cout.rdbuf(outputFile.rdbuf());  

        if (solution) 
        {
            for (int i = 0; i < numNodes; i++) {
                cout << "(" << i + 1 << "," << prev[i] + 1 << ")";
                
                if (i != numNodes - 1) {
                    cout << " ";
                }
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
                cout << "(" << i + 1 << "," << prev[i] + 1 << ")";
                
                if (i != numNodes - 1) {
                    cout << " ";
                }
            }
        }
        else cout << finalcost << endl;
    }
        
    return 0;
}