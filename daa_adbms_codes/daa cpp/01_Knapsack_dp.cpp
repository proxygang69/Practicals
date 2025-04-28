#include <iostream>
#include <vector>
#include <iomanip> // For formatting the output

using namespace std;

// Function to implement 0/1 Knapsack using dynamic programming
int knapsack(int W, const vector<int>& weights, const vector<int>& profits, int n, vector<vector<int>>& dp) {
    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weights[i - 1] <= w) {
                // Either include the item or exclude it, and take the maximum profit
                dp[i][w] = max(profits[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                // Exclude the item
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The bottom-right cell of the table will contain the maximum profit
    return dp[n][W];
}

// Function to display the DP table
void displayDPTable(const vector<vector<int>>& dp) {
    cout << "\nDP Table:\n";
    for (const auto& row : dp) {
        for (int value : row) {
            cout << setw(4) << value; // setw for alignment
        }
        cout << endl;
    }
}

int main() {
    int n, W;
    cout << "Enter the number of items: ";
    cin >> n;
    cout << "Enter the maximum capacity of the knapsack: ";
    cin >> W;

    vector<int> weights(n), profits(n);

    cout << "Enter the weights of the items: ";
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    cout << "Enter the profits of the items: ";
    for (int i = 0; i < n; i++) {
        cin >> profits[i];
    }

    // Create a DP table initialized to 0
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    int maxProfit = knapsack(W, weights, profits, n, dp);
    cout << "The maximum profit is: " << maxProfit << endl;

    // Display the DP table
    displayDPTable(dp);

    return 0;
}
