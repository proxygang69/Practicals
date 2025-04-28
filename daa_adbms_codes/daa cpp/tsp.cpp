#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Node {
    vector<int> path;
    int reducedCostMatrix[10][10];
    int cost;
    int vertex;
    int level;

    Node(int n) : cost(0), vertex(-1), level(0) {
        path = vector<int>(n, -1);
    }
};

// Function to reduce a matrix and return the reduction cost
int reduceMatrix(int matrix[10][10], int n) {
    int reductionCost = 0;

    // Row reduction
    for (int i = 0; i < n; i++) {
        int min = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        if (min != INT_MAX && min != 0) {
            reductionCost += min;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= min;
                }
            }
        }
    }

    // Column reduction
    for (int j = 0; j < n; j++) {
        int min = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        if (min != INT_MAX && min != 0) {
            reductionCost += min;
            for (int i = 0; i < n; i++) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= min;
                }
            }
        }
    }

    return reductionCost;
}

// Priority queue comparison function
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->cost > b->cost;
    }
};

void printPath(const vector<int>& path) {
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << (i == path.size() - 1 ? "\n" : " -> ");
    }
}

int tspBranchAndBound(int graph[10][10], int n) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    Node* root = new Node(n);
    root->path[0] = 0;
    root->level = 0;
    root->vertex = 0;
    
    // Copy and reduce cost matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            root->reducedCostMatrix[i][j] = graph[i][j];
        }
    }
    root->cost = reduceMatrix(root->reducedCostMatrix, n);
    
    pq.push(root);
    int minCost = INT_MAX;
    vector<int> bestPath;

    while (!pq.empty()) {
        Node* minNode = pq.top();
        pq.pop();

        if (minNode->cost >= minCost) continue;

        if (minNode->level == n - 1) {
            minNode->path[n - 1] = minNode->vertex;
            minNode->path[n] = 0;

            int finalCost = minNode->cost + graph[minNode->vertex][0];
            if (finalCost < minCost) {
                minCost = finalCost;
                bestPath = minNode->path;
            }
            continue;
        }

        for (int j = 0; j < n; j++) {
            if (minNode->reducedCostMatrix[minNode->vertex][j] != INT_MAX) {
                Node* child = new Node(n);
                child->path = minNode->path;
                child->path[minNode->level + 1] = j;
                child->level = minNode->level + 1;
                child->vertex = j;
                child->cost = minNode->cost + minNode->reducedCostMatrix[minNode->vertex][j];

                for (int i = 0; i < n; i++) {
                    for (int k = 0; k < n; k++) {
                        child->reducedCostMatrix[i][k] = minNode->reducedCostMatrix[i][k];
                    }
                }

                for (int k = 0; k < n; k++) {
                    child->reducedCostMatrix[minNode->vertex][k] = INT_MAX;
                    child->reducedCostMatrix[k][j] = INT_MAX;
                }
                child->reducedCostMatrix[j][0] = INT_MAX;

                child->cost += reduceMatrix(child->reducedCostMatrix, n);
                if (child->cost < minCost) {
                    pq.push(child);
                }
            }
        }
    }

    cout << "Minimum cost: " << minCost << endl;
    cout << "Path: ";
    printPath(bestPath);

    return minCost;
}

int main() {
    int n;
    cout << "Enter the number of cities: ";
    cin >> n;

    int graph[10][10];
    cout << "Enter the cost matrix (use 9999 for no direct path):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
            if (graph[i][j] == 9999) {
                graph[i][j] = INT_MAX;
            }
        }
    }

    tspBranchAndBound(graph, n);

    return 0;
}
