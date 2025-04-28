package NQueens;
import java.util.*; // Importing necessary classes from the java.util package

// Class to encapsulate the N-Queens problem solution
class Chessboard {
    // Method to solve the N-Queens problem and return all arrangements
    public static List<List<String>> solveNQueens(int n) {
        char[][] board = new char[n][n]; // Create a n x n chessboard
        for (int i = 0; i < n;i++) // Fill the board with '.' (representing empty squares)
            Arrays.fill(board[i], '.'); // Initialize each row with empty squares

        List<List<String>> res = new ArrayList<>(); // List to store all valid arrangements
        dfs(0, board, res); // Start the DFS from the first column
        return res; // Return the list of arrangements found
    }

    // Method to validate if a queen can be placed at (row, col)
    static boolean validate(char[][] board, int row, int col) {
        int duprow = row; // Store the current row for future reference
        int dupcol = col; // Store the current column for future reference

        // Check upper left diagonal
        while (row >= 0 && col >= 0) {
            if (board[row][col] == 'Q') return false; // If a queen is found, return false
            row--; // Move to the upper row
            col--; // Move to the left column
        }

        row = duprow; // Restore original row
        col = dupcol; // Restore original column

        // Check the current row
        while (col >= 0) {
            if (board[row][col] == 'Q') return false; // If a queen is found, return false
            col--; // Move left
        }

        row = duprow; // Restore original row
        col = dupcol; // Restore original column

        // Check lower left diagonal
        while (col >= 0 && row < board.length) {
            if (board[row][col] == 'Q') return false; // If a queen is found, return false
            col--; // Move left
            row++; // Move down
        }
        return true; // If no queens threaten the position, return true
    }

    // Depth-First Search method to place queens
    static void dfs(int col, char[][] board, List<List<String>> res) {
        // If all queens are placed (base case)
        if (col == board.length) {
            List<String> arrangement = construct(board); // Construct the current valid arrangement
            res.add(arrangement); // Add it to the result list
            System.out.println("Final Arrangement found:"); // Print the found arrangement
            for (String s : arrangement) {
                System.out.println(s); // Print each row of the arrangement
            }
            System.out.println(); // New line for better readability
            return; // Return to continue searching for other arrangements
        }

        boolean placed = false; // Track if a queen was placed in this column

        // Iterate over each row in the current column
        for (int row = 0; row < board.length; row++) {
            if (validate(board, row, col)) { // Check if placing a queen is valid
                board[row][col] = 'Q'; // Place the queen on the board
                System.out.println("Placing Q at (" + row + ", " + col + "):"); // Log the placement
                printBoard(board); // Print the current state of the board
                placed = true; // Mark that a queen was placed

                dfs(col + 1, board, res); // Recur to place queens in the next column

                // Backtrack: remove the queen from the current position
                board[row][col] = '.'; 
            }
        }

        // Indicate backtracking if no placement was found in this column
        if (!placed) {
            System.out.println("No valid placement for column " + col + ", backtracking...");
        }
    }

    // Construct a list of strings representing the board arrangement
    static List<String> construct(char[][] board) {
        List<String> res = new ArrayList<>(); // List to hold the string representation of the board
        for (int i = 0; i < board.length; i++) {
            res.add(new String(board[i])); // Convert each row to a string and add to the list
        }
        return res; // Return the constructed arrangement
    }

    // Method to print the current state of the chessboard
    static void printBoard(char[][] board) {
        for (char[] row : board) {
            System.out.println(new String(row)); // Print each row of the board
        }
        System.out.println(); // New line for better readability
    }
}

// Main class to execute the program
public class NQueens2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in); // Scanner for user input
        System.out.print("Enter the number of queens (N): "); // Prompt user for input
        int N = scanner.nextInt(); // Read the number of queens
        List<List<String>> queenArrangements = Chessboard.solveNQueens(N); // Solve the N-Queens problem
        
        System.out.println("Total arrangements are: " + queenArrangements.size()); // Print the total number of arrangements
        scanner.close(); // Close the scanner to avoid resource leak
    }
}
