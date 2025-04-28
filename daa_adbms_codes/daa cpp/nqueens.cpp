#include <iostream>
#include <vector>

using namespace std;

void printBoard(const vector<int>& queens, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (queens[i] == j ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

bool isSafe(const vector<int>& queens, int row, int col) {
    for (int i = 0; i < row; i++) {
        int placedCol = queens[i];
        if (placedCol == col || abs(placedCol - col) == abs(i - row)) {
            return false;  // Same column or diagonal conflict
        }
    }
    return true;
}

bool solveNQueensUtil(vector<int>& queens, int row, int N) {
    if (row == N) {
        cout << "Solution found:\n";
        printBoard(queens, N);
        return true;
    }

    for (int col = 0; col < N; col++) {
        cout << "Trying to place queen at (" << row << ", " << col << ")\n";

        if (isSafe(queens, row, col)) {
            queens[row] = col;
            cout << "Placed queen at (" << row << ", " << col << "):\n";
            printBoard(queens, N);

            if (solveNQueensUtil(queens, row + 1, N)) return true;

            // Backtracking step
            queens[row] = -1;
            cout << "Backtracking from (" << row << ", " << col << "):\n";
            printBoard(queens, N);
        } else {
            cout << "Cannot place queen at (" << row << ", " << col << ") - Not safe\n";
        }
    }

    return false;
}

void solveNQueens(int N) {
    vector<int> queens(N, -1);  // Each entry represents the column position of the queen in each row

    if (!solveNQueensUtil(queens, 0, N)) {
        cout << "No solution exists for " << N << " queens.\n";
    }
}

int main() {
    int N;
    cout << "Enter the number of queens: ";
    cin >> N;

    solveNQueens(N);

    return 0;
}
