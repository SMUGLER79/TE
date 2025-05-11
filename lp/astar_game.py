import heapq

# Define the 8-puzzle problem
class Puzzle:
    def __init__(self, board, size=3):
        self.board = board
        self.size = size
        self.blank_pos = self.board.index(0)  # Position of the blank (0)
        self.goal = list(range(1, size*size)) + [0]  # Goal state

    # Return possible actions (swaps) for the blank space
    def get_neighbors(self):
        neighbors = []
        x, y = self.blank_pos // self.size, self.blank_pos % self.size
        
        # Possible moves: up, down, left, right
        moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        
        for dx, dy in moves:
            new_x, new_y = x + dx, y + dy
            if 0 <= new_x < self.size and 0 <= new_y < self.size:
                new_pos = new_x * self.size + new_y
                new_board = self.board[:]
                # Swap the blank space with the adjacent tile
                new_board[self.blank_pos], new_board[new_pos] = new_board[new_pos], new_board[self.blank_pos]
                neighbors.append(Puzzle(new_board))
        return neighbors

    # Manhattan distance heuristic (sum of tile distances)
    def heuristic(self):
        distance = 0
        for i, tile in enumerate(self.board):
            if tile == 0: continue  # Skip the blank space
            goal_pos = self.goal.index(tile)
            x1, y1 = i // self.size, i % self.size
            x2, y2 = goal_pos // self.size, goal_pos % self.size
            distance += abs(x1 - x2) + abs(y1 - y2)
        return distance

    # Check if the puzzle is solved
    def is_goal(self):
        return self.board == self.goal

    def __str__(self):
        return '\n'.join([str(self.board[i:i+self.size]) for i in range(0, len(self.board), self.size)])

# A* search algorithm
def a_star_search(start_puzzle):
    open_list = []
    closed_list = set()
    
    # Start node with f(n) = g(n) + h(n)
    start_node = (start_puzzle.heuristic(), 0, start_puzzle)
    heapq.heappush(open_list, start_node)
    
    while open_list:
        _, g, current_puzzle = heapq.heappop(open_list)
        
        if current_puzzle.is_goal():
            return current_puzzle
        
        closed_list.add(tuple(current_puzzle.board))
        
        for neighbor in current_puzzle.get_neighbors():
            if tuple(neighbor.board) in closed_list:
                continue
            
            h = neighbor.heuristic()
            f = g + 1 + h  # f(n) = g(n) + h(n)
            heapq.heappush(open_list, (f, g + 1, neighbor))
    
    return None  # No solution found

# Test the implementation
if __name__ == "__main__":
    initial_state = [1, 2, 3, 4, 0, 5, 6, 7, 8]  # Initial configuration
    puzzle = Puzzle(initial_state)
    
    print("Initial State:")
    print(puzzle)
    
    solution = a_star_search(puzzle)
    
    if solution:
        print("\nSolved Puzzle:")
        print(solution)
    else:
        print("No solution found.")
