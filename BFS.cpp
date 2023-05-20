#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void bfs(vector<vector<int>>& graph, int startNode,int prev[],int dist[], int pai[]) {
    int numNodes = graph.size();
    //vector<bool> visited(numNodes, false);
    queue<int> q;
    int cont = 0;
    prev[startNode] = cont++;
    dist[startNode] = 0;
    pai[startNode] = -1;
    //visited[startNode] = true;
    q.push(startNode);

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();
        cout << currentNode + 1 << " ";

        for (int i = 0; i < numNodes; i++) {
            if (graph[currentNode][i] && prev[i] == -1) {
                prev[i]= cont++;
                dist[i] = dist[currentNode] + 1;
                pai[i] = currentNode;
                q.push(i);
            }
        }
    }
}

int main() {
    int numNodes, numEdges;
    cout << "Enter the number of nodes: ";
    cin >> numNodes;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    vector<vector<int>> graph(numNodes, vector<int>(numNodes, 0));

    cout << "Enter the edges:\n";
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1; // Assuming an undirected graph
    }
    int prev[numNodes];
    int dist[numNodes];
    int pai[numNodes];

    for(int i = 0; i < numNodes; i++)
    {
        prev[i] = -1;
        dist[i] = -1;
        pai[i] = -1;
    }

    cout << "BFS traversal starting from node " << 1 << ": ";
    bfs(graph, 0, prev, dist, pai);
    cout << endl;
    for(int i = 0; i < numNodes; i++)
    {
        cout << "Vertex " << i << " was visited in the " << prev[i] + 1  << " iteration." << endl; 
    }

    for(int i = 0; i < numNodes; i++)
    {
        cout << "Vertex " << i << " has a distance of " << dist[i]  << " vertices from starting vertex 0" << endl; 
    }

    for(int i = 0; i < numNodes; i++)
    {
        cout << "Vertex " << i << " is the son of vertex " << pai[i] << endl; 
    }


    return 0;
}
