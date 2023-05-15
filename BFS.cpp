#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void bfs(vector<vector<int>>& graph, int startNode) {
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false);
    queue<int> q;

    visited[startNode] = true;
    q.push(startNode);

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();
        cout << currentNode << " ";

        for (int i = 0; i < numNodes; i++) {
            if (graph[currentNode][i] && !visited[i]) {
                visited[i] = true;
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

    int startNode;
    cout << "Enter the starting node: ";
    cin >> startNode;

    cout << "BFS traversal starting from node " << startNode << ": ";
    bfs(graph, startNode);
    cout << endl;

    return 0;
}
