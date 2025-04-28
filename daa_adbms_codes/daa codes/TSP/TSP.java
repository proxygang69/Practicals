package TSP;

import java.util.Arrays;
import java.util.Scanner;

class TSP {
    private int numCities;           // Number of cities
    private int[][] costMatrix;      // Matrix representing the cost of traveling between cities
    private int[] bestPath;          // To store the best path (optimal solution)
    private int bestCost = Integer.MAX_VALUE; // To store the minimum cost found

    // Constructor: Initializes the TSP instance with the cost matrix
    public TSP(int[][] costMatrix) {
        this.costMatrix = costMatrix;
        this.numCities = costMatrix.length;  // Set number of cities from the cost matrix size
        this.bestPath = new int[numCities + 1];  // To store the path, including the return to the starting city
    }

    // Method to find the optimal tour using the branch and bound technique
    public void findOptimalTour() {
        boolean[] visited = new boolean[numCities];  // Track which cities have been visited
        int[] currentPath = new int[numCities + 1];  // Array to store the current path
        visited[0] = true;  // Start from the first city
        currentPath[0] = 0;  // Starting city is city 0 (index 0)

        // Start the branch and bound process from city 0, cost 0, at level 1
        branchAndBound(0, 0, 1, visited, currentPath);
    }

    // Recursive method implementing the branch and bound algorithm
    private void branchAndBound(int currentCity, int currentCost, int level, boolean[] visited, int[] currentPath) {
        if (level == numCities) {
            // If all cities have been visited, complete the tour by returning to the starting city (0)
            int totalCost = currentCost + costMatrix[currentCity][0];  // Add the return cost to the starting city
            if (totalCost < bestCost) {
                // If the new tour cost is better, update the best path and cost
                bestCost = totalCost;
                System.arraycopy(currentPath, 0, bestPath, 0, numCities); // Copy the current path to bestPath
                bestPath[numCities] = 0;  // Set the last city as the starting city (return to start)
            }
            return;  // End recursion as the tour is complete
        }

        // Try every possible city as the next city to visit
        for (int nextCity = 0; nextCity < numCities; nextCity++) {
            if (!visited[nextCity]) {  // If the city hasn't been visited
                visited[nextCity] = true;  // Mark it as visited
                currentPath[level] = nextCity;  // Add it to the current path

                // Calculate the new cost to travel to the next city
                int newCost = currentCost + costMatrix[currentCity][nextCity];

                // Only proceed if the new cost is promising (i.e., less than the current best cost)
                if (newCost < bestCost) {
                    branchAndBound(nextCity, newCost, level + 1, visited, currentPath);  // Recurse for the next city
                }

                // Backtrack: Unmark the current city and remove it from the path
                visited[nextCity] = false;
            }
        }
    }

    // Method to print the result (optimal path and minimum cost)
    public void printResult() {
        System.out.println("Optimal Path: " + Arrays.toString(bestPath));  // Print the best path
        System.out.println("Minimum Cost: " + bestCost);  // Print the minimum cost of the tour
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);  // Create a Scanner object for user input

        // Prompt user for number of cities
        System.out.print("Enter the number of cities: ");
        int n = scanner.nextInt();  // Read number of cities

        // Initialize the cost matrix based on the number of cities
        int[][] costMatrix = new int[n][n];

        // Prompt user to enter the cost matrix (cost of travel between cities)
        System.out.println("Enter the cost matrix:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                costMatrix[i][j] = scanner.nextInt();  // Read the cost for each pair of cities
            }
        }

        // Create an instance of TSP with the given cost matrix
        TSP tsp = new TSP(costMatrix);

        // Find the optimal tour using branch and bound
        tsp.findOptimalTour();

        // Print the result (optimal path and minimum cost)
        tsp.printResult();

        scanner.close();  // Close the scanner object to avoid resource leaks
    }
}


