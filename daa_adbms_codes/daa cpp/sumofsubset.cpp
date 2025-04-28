#include <iostream>
#include <vector>

using namespace std;

void printSubset(const vector<int>& subset) {
    cout << "{ ";
    for (int num : subset) {
        cout << num << " ";
    }
    cout << "}\n";
}

void subsetSumUtil(const vector<int>& nums, vector<int>& subset, int index, int targetSum, int currentSum) {
    // Base case: If the current sum equals the target sum, print the subset
    if (currentSum == targetSum) {
        cout << "Found subset: ";
        printSubset(subset);
        return;
    }

    // If the current sum exceeds the target sum or no elements are left to process
    if (currentSum > targetSum || index >= nums.size()) {
        return;
    }

    // Include the current element in the subset
    subset.push_back(nums[index]);
    // cout << "Including " << nums[index] << " in subset, current subset: ";
    // printSubset(subset);
    subsetSumUtil(nums, subset, index + 1, targetSum, currentSum + nums[index]);

    // Backtrack: Exclude the current element from the subset
    subset.pop_back();
    // cout << "Excluding " << nums[index] << " from subset, backtracking to subset: ";
    // printSubset(subset);
    subsetSumUtil(nums, subset, index + 1, targetSum, currentSum);
}

void subsetSum(const vector<int>& nums, int targetSum) {
    vector<int> subset;
    subsetSumUtil(nums, subset, 0, targetSum, 0);
}

int main() {
    int n, targetSum;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << "Enter the target sum: ";
    cin >> targetSum;

    cout << "\nSubsets with sum " << targetSum << ":\n";
    subsetSum(nums, targetSum);

    return 0;
}
