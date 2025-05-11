from heapq import heappush, heappop

# Check if the current color assignment is safe
def is_safe(node, color, graph, colors):
    for neighbor in graph[node]:
        if colors[neighbor] == color:
            return False
    return True

# ----- BACKTRACKING -----
def graph_coloring_backtrack(graph, m, colors, node, solution_count, max_solutions):
    if solution_count[0] >= max_solutions:
        return

    if node == len(graph):
        print("Solution", solution_count[0] + 1, ":", colors)
        solution_count[0] += 1
        return

    for c in range(1, m + 1):
        if is_safe(node, c, graph, colors):
            colors[node] = c
            graph_coloring_backtrack(graph, m, colors, node + 1, solution_count, max_solutions)
            colors[node] = 0

# ----- BRANCH & BOUND -----
def get_conflicts(graph, colors):
    conflicts = 0
    for u in range(len(graph)):
        for v in graph[u]:
            if colors[u] != 0 and colors[u] == colors[v]:
                conflicts += 1
    return conflicts // 2  # each conflict counted twice

def graph_coloring_branch_bound(graph, m, max_solutions):
    n = len(graph)
    colors = [0] * n
    queue = [(0, colors[:])]
    solution_count = 0

    while queue and solution_count < max_solutions:
        _, current_colors = heappop(queue)
        node = next((i for i in range(n) if current_colors[i] == 0), n)

        if node == n:
            print("Solution", solution_count + 1, ":", current_colors)
            solution_count += 1
            continue

        for c in range(1, m + 1):
            if is_safe(node, c, graph, current_colors):
                new_colors = current_colors[:]
                new_colors[node] = c
                heappush(queue, (get_conflicts(graph, new_colors), new_colors))

# ----- DRIVER -----
def menu():
    graph = {
        0: [1, 2],
        1: [0, 2, 3],
        2: [0, 1, 3],
        3: [1, 2]
    }  # Example: A 4-node undirected graph

    while True:
        print("\n1. Graph Coloring using Backtracking")
        print("2. Graph Coloring using Branch & Bound")
        print("3. Exit")
        ch = input("Choose option: ")
        if ch == '3':
            break

        m = int(input("Enter number of colors: "))
        k = int(input("Enter max number of solutions to display: "))

        if ch == '1':
            colors = [0] * len(graph)
            graph_coloring_backtrack(graph, m, colors, 0, [0], k)
        elif ch == '2':
            graph_coloring_branch_bound(graph, m, k)
        else:
            print("Invalid option.")

if __name__ == "__main__":
    menu()
