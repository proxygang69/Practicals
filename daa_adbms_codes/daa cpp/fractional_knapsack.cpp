#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an item with weight and value
struct Item {
    int weight;
    int value;
};

// Comparator function to sort items by value/weight ratio in descending order
bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

// Function to calculate the maximum value for the fractional knapsack problem
double fractionalKnapsack(int W, vector<Item>& items) {
    // Sort items by value-to-weight ratio
    sort(items.begin(), items.end(), compare);

    double maxValue = 0.0;  // Maximum value that can be attained
    int currentWeight = 0;  // Current weight in the knapsack

    for (auto item : items) {
        // If adding the entire item won't exceed capacity
        if (currentWeight + item.weight <= W) {
            currentWeight += item.weight;
            maxValue += item.value;
        }
        // If we can only take a fraction of the remaining item
        else {
            int remain = W - currentWeight;
            maxValue += item.value * ((double)remain / item.weight);
            break;
        }
    }

    return maxValue;
}

int main() {
    int n, W;
    cout << "Enter the number of items: ";
    cin >> n;
    cout << "Enter the capacity of the knapsack: ";
    cin >> W;

    vector<Item> items(n);
    cout << "Enter weight and value for each item:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight >> items[i].value;
    }

    double maxProfit = fractionalKnapsack(W, items);
    cout << "Maximum value in Knapsack = " << maxProfit << endl;

    return 0;
}
