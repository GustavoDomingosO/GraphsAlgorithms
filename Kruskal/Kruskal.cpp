#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct UnionFind
{
    vector<int> parent, rank;

    UnionFind(int n) { //n = num of vertices
        parent.resize(n);
        rank.resize(n, 0);
        
        // Initialize each node as a separate set with itself as the parent
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int Find(int v)
    {
        if (parent[v] != v) parent[v] = Find(parent[v]);
        return parent[v];
    }

    void Union(int v, int u)
    {
        if (rank[v] > rank[u])
        {
            parent[u] = v;
        }
        else if (rank[v] < rank[u])
        {
            parent[v] = u;
        }
        else
        {
            parent[v] = u;
            rank[u]++;
        }
    }
};

bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

vector<Edge> Kruskal(vector<Edge>& edges, int numNodes, int initialVertex)
{
    vector<Edge> mst;
    sort(edges.begin(), edges.end(), compareEdges);

    UnionFind union1(numNodes);
    union1.Union(initialVertex, initialVertex);  // Connect the initial vertex to itself

    for (int i = 0; i < edges.size(); i++) 
    {
        int srcParent = union1.Find(edges[i].src);
        int destParent = union1.Find(edges[i].dest);
        
        if (srcParent != destParent)
        {
            mst.push_back(edges[i]);
            union1.Union(srcParent, destParent);
        }
    }
    
    return mst;
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

    int numNodes, numEdges, u, v, weight;

    ifstream inputFile(inputFilename);
 
    inputFile >> numNodes >> numEdges;

    vector<Edge> edges(numEdges);

    for (int i = 0; i < numEdges; ++i) {
        inputFile >> u >> v >> weight;
        edges[i] = {u-1,v-1,weight};
    }
    inputFile.close();

    vector<Edge> mst = Kruskal(edges, numNodes, initialVertex - 1);

    int finalcost = 0;

    for (const auto& edge : mst) {
      finalcost += edge.weight;
    }


    if(!outputFilename.empty())
    {
        ofstream outputFile("output.txt");
        if (outputFile.is_open()) {
        streambuf* originalCoutBuffer = std::cout.rdbuf();  // Store the original cout buffer
        cout.rdbuf(outputFile.rdbuf());  

        if (solution) 
        {
            for (size_t i = 0; i < mst.size(); i++) {
                const auto& edge = mst[i];
                cout << "(" << edge.src + 1 << "," << edge.dest + 1 << ")";
                
                // Print a space if it's not the last element
                if (i != mst.size() - 1) {
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
            for (size_t i = 0; i < mst.size(); i++) {
                const auto& edge = mst[i];
                cout << "(" << edge.src + 1 << "," << edge.dest + 1 << ")";
                
                // Print a space if it's not the last element
                if (i != mst.size() - 1) {
                    cout << " ";
                }
            }
        }
        else cout << finalcost << endl;
    }

    return 0;
}