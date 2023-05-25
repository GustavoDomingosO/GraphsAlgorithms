#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <climits>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct UnionFind
{
    vector<int> parent, rank;

    UnionFind(int n) { 
        parent.resize(n);
        rank.resize(n, 0);
        
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


    sort(mst.begin(), mst.end(), [](const Edge& edge1, const Edge& edge2) {
        return edge1.src < edge2.src;
    });     

    int finalcost = 0;

    for (const auto& edge : mst) {
      finalcost += edge.weight;
    }


    if(!outputFilename.empty())
    {
        ofstream outputFile(outputFilename);
        if (outputFile.is_open()) {
        streambuf* originalCoutBuffer = std::cout.rdbuf();
        cout.rdbuf(outputFile.rdbuf());  

        if (solution) 
        {
            for (size_t i = 0; i < mst.size(); i++) {
                const auto& edge = mst[i];
                cout << "(" << edge.src + 1 << "," << edge.dest + 1 << ")";
                
                if (i != mst.size() - 1)cout << " ";
                else cout << endl;
            }
        }
        else cout << finalcost << endl;

        std::cout.rdbuf(originalCoutBuffer);
        outputFile.close();
        }
    }    
    else {
        if (solution) 
        {
            for (size_t i = 0; i < mst.size(); i++) {
                const auto& edge = mst[i];
                cout << "(" << edge.src + 1 << "," << edge.dest + 1 << ")";
                
                if (i != mst.size() - 1) cout << " ";
                else cout << endl;
            }
        }
        else cout << finalcost << endl;
    }

    return 0;
}