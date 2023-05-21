#include <iostream>
#include <queue>
#include <vector>

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

int main() {
    int numNodes, numEdges;
    cin >> numNodes;
    cin >> numEdges;

    vector<vector<int>> graph(numNodes, vector<int>(numNodes, -1));

    for (int i = 0; i < numEdges; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        graph[u-1][v-1] = cost;
        graph[v-1][u-1] = cost;
    }

    int prev[numNodes];
    int cost_array[numNodes];

    for(int i = 0; i < numNodes; i++)
    {
        prev[i] = -1;
        cost_array[i] =  INT_MAX;
    }
    int source = 0;

    Prim(graph, source, prev, cost_array, numNodes);

    for(int i = 0; i< numNodes; i++)
    {
        cout << "Vertex " << i + 1 << " Has a cost of " << cost_array[i] << " and is the son of " << prev[i] + 1 << endl;
    }


    return 0;
}