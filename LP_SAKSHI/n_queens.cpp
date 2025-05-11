#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
using namespace std;

int solutionCount = 0;

// Function to print the board
void printBoard(const vector<int>& board, int n) {
    cout << "\nSolution " << ++solutionCount << ":\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i] == j)
                cout << " Q ";
            else
                cout << " . ";
        }
        cout << endl;
    }
}

// ---------- Backtracking Implementation ----------
bool isSafeBacktrack(const vector<int>& board, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return false;
    }
    return true;
}

void solveBacktrack(vector<int>& board, int row, int n) {
    if (row == n) {
        printBoard(board, n);
        return;
    }
    for (int col = 0; col < n; col++) {
        if (isSafeBacktrack(board, row, col)) {
            board[row] = col;
            solveBacktrack(board, row + 1, n);
        }
    }
}

// ---------- Branch & Bound Implementation ----------
void solveBranchBound(int row, int n, vector<int>& board,
                      vector<bool>& col, vector<bool>& diag1, vector<bool>& diag2) {
    if (row == n) {
        printBoard(board, n);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!col[i] && !diag1[row - i + n - 1] && !diag2[row + i]) {
            board[row] = i;
            col[i] = diag1[row - i + n - 1] = diag2[row + i] = true;

            solveBranchBound(row + 1, n, board, col, diag1, diag2);

            col[i] = diag1[row - i + n - 1] = diag2[row + i] = false;
        }
    }
}

// ---------- Main Menu ----------
int main() {
    int n, choice;
    do {
        cout << "\n--- N-Queens Solver Menu ---\n";
        cout << "1. Solve using Backtracking\n";
        cout << "2. Solve using Branch and Bound\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            cout << "Enter the value of N (size of board): ";
            cin >> n;
            if (n < 1 || n > 15) {
                cout << "Please enter N between 1 and 15.\n";
                continue;
            }

            vector<int> board(n, -1);
            solutionCount = 0;

            if (choice == 1) {
                cout << "\nSolving using Backtracking...\n";
                solveBacktrack(board, 0, n);
            } else {
                cout << "\nSolving using Branch and Bound...\n";
                vector<bool> col(n, false), diag1(2 * n - 1, false), diag2(2 * n - 1, false);
                solveBranchBound(0, n, board, col, diag1, diag2);
            }

            if (solutionCount == 0)
                cout << "No solutions found.\n";
            else
                cout << "\nTotal solutions found: " << solutionCount << endl;
        }
    } while (choice != 3);

    cout << "Exiting program. Goodbye!\n";
    return 0;
}