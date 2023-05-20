#include <iostream>
#include <queue>
#include <vector>

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

int main() {
    int numNodes, numEdges;
    cin >> numNodes;
    cin >> numEdges;

    vector<vector<int>> graph(numNodes, vector<int>(numNodes, -1));

    for (int i = 0; i < numEdges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph[u-1][v-1] = weight;
        graph[v-1][u-1] = weight;
    }


    int prev[numNodes];
    int dist[numNodes];

    for(int i = 0; i < numNodes; i++)
    {
        prev[i] = -1;
        dist[i] =  999;
    }
    int source = 0;

    Dijkstra(graph, source, dist, prev,  numNodes);

    for(int i = 0; i < numNodes; i++)
    {
        cout << "Vertex " << i + 1 << " has a distance of " << dist[i] << " from the source node and is the son of " << prev[i]<< endl; 
    }

    return 0;
}