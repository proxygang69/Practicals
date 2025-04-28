#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

// Edge structure to store source, destination, and weight of each edge
struct Edge {
    int src, dest, weight;
};

// Bellman-Ford function to find the shortest path
void bellmanFord(int V, int E, vector<Edge>& edges, int source) {
    // Initialize distances from the source to all vertices as infinite
    vector<int> distance(V, INT_MAX);
    distance[source] = 0;

    // Relax all edges |V| - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    // Check for negative-weight cycles
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;
        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            cout << "Graph contains a negative-weight cycle" << endl;
            return;
        }
    }

    // Print distances to each vertex
    cout << "Vertex Distance from Source" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "\t\t" << distance[i] << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;
    vector<Edge> edges(E);

    cout << "Enter each edge (source, destination, weight):" << endl;
    for (int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    bellmanFord(V, E, edges, source);

    return 0;
}
