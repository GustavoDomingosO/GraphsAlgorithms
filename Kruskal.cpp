#include <iostream>
#include <vector>
#include <algorithm>

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

vector<Edge> Kruskal(vector<Edge>& edges, int numNodes)
{
    vector<Edge> mst;
    sort(edges.begin(), edges.end(), compareEdges);

    UnionFind union1(numNodes);

    for (int i = 0; i < edges.size(); i++) 
    {
        int srcParent = union1.Find(edges[i].src);
        int destParent = union1.Find(edges[i].dest);
        if(srcParent != destParent)
        {
            mst.push_back(edges[i]);
            union1.Union(srcParent,destParent);
        }
    }
    return mst;
}

int main() {
    int numNodes, numEdges;
    cin >> numNodes;
    cin >> numEdges;

    vector<Edge> edges(numEdges);

    for (int i = 0; i < numEdges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        edges[i] = {u-1,v-1,weight};
    }

    vector<Edge> mst = Kruskal(edges, numNodes);

    cout << "Minimum Spanning Tree:\n";
    for (const auto& edge : mst) {
        cout << edge.src + 1 << " -- " << edge.dest + 1 << " : " << edge.weight << "\n";
    }


    return 0;
}