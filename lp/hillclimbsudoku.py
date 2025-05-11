import random

# Define Sudoku board dimensions
N = 9
GRID_SIZE = 3  # Subgrid size

# Example Sudoku Puzzle (0 represents an empty cell)
initial_board = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9]
]

# Utility function to print the board
def print_board(board):
    for row in board:
        print(" ".join(str(num) if num != 0 else '.' for num in row))

# Check conflicts in rows, columns, and subgrids
def count_conflicts(board):
    conflicts = 0

    # Row conflicts
    for row in board:
        conflicts += len(row) - len(set(row))  # duplicate values in row

    # Column conflicts
    for col in range(N):
        column = [board[row][col] for row in range(N)]
        conflicts += len(column) - len(set(column))  # duplicate values in column

    # Subgrid conflicts
    for i in range(0, N, GRID_SIZE):
        for j in range(0, N, GRID_SIZE):
            subgrid = [board[x][y] for x in range(i, i + GRID_SIZE) for y in range(j, j + GRID_SIZE)]
            conflicts += len(subgrid) - len(set(subgrid))  # duplicate values in subgrid

    return conflicts

# Successor function to generate all possible boards by modifying one cell
def get_neighbors(board):
    neighbors = []
    for i in range(N):
        for j in range(N):
            if board[i][j] == 0:  # Empty cell
                for num in range(1, 10):  # Try filling the cell with a number from 1 to 9
                    new_board = [row[:] for row in board]  # Copy the current board
                    new_board[i][j] = num
                    neighbors.append(new_board)
    return neighbors

# Hill Climbing Search
def hill_climbing(board):
    current_board = [row[:] for row in board]
    current_conflicts = count_conflicts(current_board)
    while current_conflicts > 0:
        neighbors = get_neighbors(current_board)
        next_board = None
        next_conflicts = current_conflicts

        # Select the neighbor with the least number of conflicts
        for neighbor in neighbors:
            neighbor_conflicts = count_conflicts(neighbor)
            if neighbor_conflicts < next_conflicts:
                next_board = neighbor
                next_conflicts = neighbor_conflicts

        # If no improvement, stop
        if next_conflicts >= current_conflicts:
            print("Local maximum reached. No further improvement.")
            break

        # Move to the next state
        current_board = next_board
        current_conflicts = next_conflicts

        print_board(current_board)
        print(f"Conflicts: {current_conflicts}\n")

    if current_conflicts == 0:
        print("Sudoku solved!")
        print_board(current_board)
    else:
        print("Failed to solve the Sudoku.")

# Main function to run the hill climbing algorithm
if __name__ == "__main__":
    print("Initial Board:")
    print_board(initial_board)
    print("\nSolving Sudoku using Hill Climbing...\n")
    hill_climbing(initial_board)
