#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <algorithm>

using namespace std;

const int SIZE = 9;

vector<vector<int> > puzzle(SIZE, vector<int>(SIZE, 0));
vector<vector<bool> > isFixed(SIZE, vector<bool>(SIZE, false));

// Utility function to print the puzzle
void printPuzzle() {
    cout << "Current Sudoku Puzzle:\n";
    for (int i = 0; i < SIZE; ++i) {
        if (i % 3 == 0 && i != 0)
            cout << "------+-------+------\n";
        for (int j = 0; j < SIZE; ++j) {
            if (j % 3 == 0 && j != 0)
                cout << "| ";
            cout << puzzle[i][j] << ' ';
        }
        cout << endl;
    }
}

// Let user enter the puzzle (0 for empty)
void enterPuzzle() {
    cout << "Enter the Sudoku Puzzle (use 0 for empty cells):\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cin >> puzzle[i][j];
            isFixed[i][j] = (puzzle[i][j] != 0);
        }
    }
}

// Initialize random values in non-fixed cells
void randomInitialize() {
    for (int i = 0; i < SIZE; ++i) {
        vector<bool> present(10, false);
        for (int j = 0; j < SIZE; ++j) {
            if (isFixed[i][j])
                present[puzzle[i][j]] = true;
        }
        vector<int> missing;
        for (int val = 1; val <= 9; ++val) {
            if (!present[val])
                missing.push_back(val);
        }

        random_shuffle(missing.begin(), missing.end());
        int idx = 0;
        for (int j = 0; j < SIZE; ++j) {
            if (!isFixed[i][j]) {
                puzzle[i][j] = missing[idx++];
            }
        }
    }
}

// Heuristic function: counts number of conflicts
int countConflicts() {
    int conflicts = 0;

    // Row and column conflicts
    for (int i = 0; i < SIZE; ++i) {
        vector<int> row(10, 0), col(10, 0);
        for (int j = 0; j < SIZE; ++j) {
            row[puzzle[i][j]]++;
            col[puzzle[j][i]]++;
        }
        for (int val = 1; val <= 9; ++val) {
            if (row[val] > 1)
                conflicts += row[val] - 1;
            if (col[val] > 1)
                conflicts += col[val] - 1;
        }
    }

    // 3x3 box conflicts
    for (int boxRow = 0; boxRow < 3; ++boxRow) {
        for (int boxCol = 0; boxCol < 3; ++boxCol) {
            vector<int> box(10, 0);
            for (int i = boxRow * 3; i < boxRow * 3 + 3; ++i) {
                for (int j = boxCol * 3; j < boxCol * 3 + 3; ++j) {
                    box[puzzle[i][j]]++;
                }
            }
            for (int val = 1; val <= 9; ++val) {
                if (box[val] > 1)
                    conflicts += box[val] - 1;
            }
        }
    }

    return conflicts;
}

// Try swapping two non-fixed cells in the same row
bool hillClimbStep() {
    int currentConflicts = countConflicts();
    for (int row = 0; row < SIZE; ++row) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = i + 1; j < SIZE; ++j) {
                if (!isFixed[row][i] && !isFixed[row][j]) {
                    swap(puzzle[row][i], puzzle[row][j]);
                    int newConflicts = countConflicts();
                    if (newConflicts < currentConflicts)
                        return true; // accepted
                    else
                        swap(puzzle[row][i], puzzle[row][j]); // revert
                }
            }
        }
    }
    return false; // no better move
}

// Main hill climbing function
void hillClimbSolve() {
    srand(time(0));
    randomInitialize();
    int steps = 0;
    while (steps < 10000) {
        int conflicts = countConflicts();
        if (conflicts == 0) {
            cout << "Solution found in " << steps << " steps!\n";
            return;
        }
        if (!hillClimbStep()) {
            cout << "Reached local optimum after " << steps << " steps. Conflicts: " << conflicts << "\n";
            break;
        }
        steps++;
    }
    printPuzzle();
}

// Menu-driven interface
int main() {
    int choice;
    do {
        cout << "\n=== Sudoku Hill Climbing Menu ===\n";
        cout << "1. Enter Puzzle\n";
        cout << "2. Solve Using Hill Climbing\n";
        cout << "3. Display Puzzle\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                enterPuzzle();
                break;
            case 2:
                hillClimbSolve();
                break;
            case 3:
                printPuzzle();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
