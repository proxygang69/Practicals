package Knapsack.DPKnapsack;
import java.util.Scanner;

public class Knapsack {

    // Function to solve the 0/1 Knapsack problem using dynamic programming
    public static int knapsack(int[] weight, int[] profit, int n, int W) {
        // Create a 2D DP array to store the maximum profit for each subproblem
        // dp[i][w] represents the maximum profit we can get with the first 'i' items
        // and a knapsack capacity of 'w'
        int[][] dp = new int[n + 1][W + 1];  // n+1 rows for items, W+1 columns for capacities

        // Build the dp array, iterating through each item and knapsack capacity
        for (int i = 1; i <= n; i++) {  // Loop through each item (i=0 corresponds to no items)
            for (int w = 0; w <= W; w++) {  // Loop through all possible knapsack capacities (0 to W)
                if (weight[i - 1] <= w) {  // If the current item's weight can fit in the knapsack
                    // Max profit is either:
                    // - Not including the item (dp[i-1][w]), or
                    // - Including the item (dp[i-1][w - weight[i-1]] + profit[i-1])
                    dp[i][w] = Math.max(dp[i - 1][w], dp[i - 1][w - weight[i - 1]] + profit[i - 1]);
                } else {
                    // If the item can't fit, we just carry over the profit without including it
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        // The last cell in the DP table dp[n][W] contains the maximum profit
        // that can be obtained with 'n' items and knapsack capacity 'W'
        return dp[n][W];
    }

    public static void main(String[] args) {
        // Create a scanner object to read input from the user
        Scanner sc = new Scanner(System.in);

        // Input the number of items
        System.out.println("Enter the number of items:");
        int n = sc.nextInt();  // Number of items

        // Create arrays to store item weights and profits
        int[] weight = new int[n];
        int[] profit = new int[n];

        // Input item profits and weights
        for (int i = 0; i < n; i++) {
            System.out.println("Enter the profit and weight for item " + (i + 1) + ":");
            profit[i] = sc.nextInt();  // Profit of item i
            weight[i] = sc.nextInt();  // Weight of item i
        }

        // Input the capacity of the knapsack
        System.out.println("Enter the capacity of the knapsack:");
        int W = sc.nextInt();  // Knapsack capacity

        // Solve the 0/1 Knapsack problem and get the maximum profit
        int maxProfit = knapsack(weight, profit, n, W);

        // Output the result: the maximum profit that can be obtained
        System.out.println("The maximum profit that can be obtained is: " + maxProfit);

        // Close the scanner
        sc.close();
    }
}










































