import java.util.ArrayList;  // Import the ArrayList class for dynamic arrays
import java.util.List;       // Import the List interface for the collection type
import java.util.Scanner;    // Import the Scanner class to take input from the user

// Define the SubsetSum class that handles finding subsets with the required sum
class SubsetSum {
    private List<Integer> arr;             // List to store the input array of integers
    private List<List<Integer>> subsets;  // List of subsets that sum to the target
    private int count;                     // Variable to count the number of valid subsets

    // Constructor to initialize the variables
    public SubsetSum() {
        arr = new ArrayList<>();           // Initialize the arr list
        subsets = new ArrayList<>();       // Initialize the subsets list
        count = 0;                         // Initialize the count to 0
    }

    // Method to input the array elements from the user
    public void input(int n) {
        Scanner scanner = new Scanner(System.in);  // Create a scanner object to read user input
        for (int i = 0; i < n; i++) {             // Loop over n elements
            System.out.print("Enter element " + (i + 1) + ": ");  // Prompt the user for input
            arr.add(scanner.nextInt());                      // Add the element to the arr list
        }
    }

    // Method to find all subsets whose sum equals the target sum
    public void findSubset(int sum) {
        List<Integer> currentSubset = new ArrayList<>();  // List to store the current subset
        backtrack(0, sum, currentSubset);  // Start the backtracking process from index 0 with the given sum
    }

    // Backtracking method to explore all possible subsets
    private void backtrack(int index, int sum, List<Integer> currentSubset) {
        // If the sum becomes 0, we found a valid subset
        if (sum == 0) {
            subsets.add(new ArrayList<>(currentSubset));  // Add the current subset to the list of subsets
            count++;  // Increment the count of valid subsets
            return;  // Return as we found a valid subset
        }
        
        // If we've reached the end of the array or the sum is negative, stop the recursion
        if (index >= arr.size() || sum < 0) {
            return;  // Exit the recursion
        }

        // Include the current element in the subset and move to the next element
        currentSubset.add(arr.get(index));  // Add the current element to the subset
        backtrack(index + 1, sum - arr.get(index), currentSubset);  // Recursively call with reduced sum

        // Exclude the current element from the subset and move to the next element
        currentSubset.remove(currentSubset.size() - 1);  // Remove the last added element from the subset
        backtrack(index + 1, sum, currentSubset);  // Recursively call without changing the sum
    }

    // Getter method to return the count of valid subsets
    public int getCount() {
        return count;  // Return the number of valid subsets
    }

    // Getter method to return the list of valid subsets
    public List<List<Integer>> getSubsets() {
        return subsets;  // Return the list of subsets
    }
}

// Main class to run the program
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);  // Create a scanner object for user input

        System.out.print("Enter the number of elements in the array: ");  // Prompt the user for the number of elements
        int n = scanner.nextInt();  // Read the number of elements
        
        SubsetSum subsetSum = new SubsetSum();  // Create an instance of SubsetSum class
        subsetSum.input(n);  // Call the input method to fill the array with elements

        System.out.print("Enter the target sum to be found: ");  // Prompt the user for the target sum
        int sum = scanner.nextInt();  // Read the target sum
        
        subsetSum.findSubset(sum);  // Call the findSubset method to find valid subsets

        // Check if any valid subsets were found
        if (subsetSum.getCount() > 0) {
            System.out.println("Number of subsets whose sum is equal to target sum: " + subsetSum.getCount());  // Print the count of valid subsets
            System.out.println("The subsets are:");  // Print a heading for the subsets
            // Loop through each subset and print it
            for (List<Integer> subset : subsetSum.getSubsets()) {
                System.out.print("{ ");  // Start the subset output
                for (Integer num : subset) {
                    System.out.print(num + " ");  // Print each number in the subset
                }
                System.out.println("}");  // End the subset output and move to the next line
            }
        } else {
            System.out.println("No subset exists whose sum is equal to target sum.");  // If no valid subsets were found, print a message
        }

        scanner.close();  // Close the scanner object to avoid resource leaks
    }
}
