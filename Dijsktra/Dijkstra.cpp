#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;


/* The input should have the vertices start at 1, example:
6 8
1 2 5
1 3 4
1 4 2
1 6 6
2 4 1
2 5 7
3 5 6
4 6 1
*/

void Dijkstra(vector<vector<int>>& graph, int source, int dist[], int prev[], int numNodes) // Minimum path algorithm for always positive weighted graph
{
    dist[source] = 0;
    //First int is the distance and the second one is the vertex.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    minHeap.push(make_pair(0, source));

    while(!minHeap.empty())
    {
        int currentNode = minHeap.top().second;
        minHeap.pop();

        //Neighbors of the current node
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
        dist[i] =  999;
    }

    Dijkstra(graph, initialVertex - 1, dist, prev,  numNodes);


    if(!outputFilename.empty())
    {
        ofstream outputFile("output.txt");
        if (outputFile.is_open()) {
        streambuf* originalCoutBuffer = std::cout.rdbuf();  // Store the original cout buffer
        cout.rdbuf(outputFile.rdbuf());  


        for(int i = 0; i < numNodes; i++)
        {
            cout << i + 1 << ":" << dist[i];
            if(i < numNodes - 1)cout << " ";
        }

        std::cout.rdbuf(originalCoutBuffer);  // Restore the original cout buffer
        outputFile.close();
        }
    }    
    else {

        for(int i = 0; i < numNodes; i++)
        {
            cout << i + 1 << ":" << dist[i];
            if(i < numNodes - 1)cout << " ";
        }
    }

    return 0;
}