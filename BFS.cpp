#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/* The input should have the vertices start at 0. Example:
10 16
0 1
0 2
0 3
1 2
1 6
2 3
2 5
2 7
3 4
4 5
4 9
5 8
5 9
6 7
7 8
8 9
*/

void bfs(vector<vector<int>>& graph, int startNode,int prev[],int dist[], int pai[]) {
    int numNodes = graph.size();
    queue<int> q;
    int cont = 0;
    prev[startNode] = cont++;
    dist[startNode] = 0;
    pai[startNode] = -1;
    q.push(startNode);

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();

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

    cin >> numNodes;
    cin >> numEdges;

    vector<vector<int>> graph(numNodes, vector<int>(numNodes, 0));

    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
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

    bfs(graph, 0, prev, dist, pai);

    for(int i = 0; i < numNodes; i++)
    {
        cout << "Vertex " << i << " was visited in the " << prev[i] + 1 << " iteration. Has a distance of " << dist[i] << " from the node 0. And is the son of " << pai[i] << endl; 
    }

    return 0;
}
