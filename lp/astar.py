import heapq

# A* algorithm implementation for a graph with alphabetic nodes
def a_star_search(graph, heuristics, start, goal):
    # Priority queue to store nodes along with their f values
    open_list = []
    heapq.heappush(open_list, (0, start))  # (f, node)
    closed_list = set()
    came_from = {}

    # g costs (distance from start)
    g_cost = {node: float('inf') for node in graph}
    g_cost[start] = 0

    # f costs (g + h)
    f_cost = {node: float('inf') for node in graph}
    f_cost[start] = heuristics[start]

    # Calculate initial node and edge counts
    node_count, edge_count = calculate_time_complexity(graph)

    print(f"Start Node: {start}, Goal Node: {goal}")
    print(f"\nGraph Information: Nodes = {node_count}, Edges = {edge_count}")
    print("Step-by-Step Calculations:")

    while open_list:
        # Get the node with the lowest f cost
        current_f, current_node = heapq.heappop(open_list)
        print(f"\nExploring Node: {current_node}, f={current_f}")

        # If we reach the goal, reconstruct and return the path
        if current_node == goal:
            path = []
            while current_node in came_from:
                path.append(current_node)
                current_node = came_from[current_node]
            path.append(start)
            path.reverse()
            # Print time complexity breakdown
            print(f"\nTime Complexity of A*:\nO((V + E) log V) = O(({node_count} + {edge_count}) log {node_count})")
            return path, g_cost[goal]

        # Mark the current node as visited
        closed_list.add(current_node)

        # Explore neighbors
        neighbors_info = []
        for neighbor, weight in graph[current_node]:
            if neighbor in closed_list:
                print(f"  Neighbor {neighbor} already visited.")
                continue

            # Calculate tentative g cost
            tentative_g_cost = weight
            h_value = heuristics[neighbor]
            f_value = tentative_g_cost + h_value

            neighbors_info.append((neighbor, tentative_g_cost, h_value, f_value))

            # If this path to neighbor is better, update
            if tentative_g_cost < g_cost[neighbor]:
                came_from[neighbor] = current_node
                g_cost[neighbor] = tentative_g_cost
                f_cost[neighbor] = f_value

                # Add neighbor to the open list if not already there
                heapq.heappush(open_list, (f_cost[neighbor], neighbor))

        # Highlight the most efficient choice among neighbors
        if neighbors_info:
            most_efficient = min(neighbors_info, key=lambda x: x[3])  # Minimum f value
            print(f"  Neighbors: {[f'{n} (g={g}, h={h}, f={f})' for n, g, h, f in neighbors_info]}")
            print(f"  Most Efficient: {most_efficient[0]} with f={most_efficient[3]}")

    # If the destination is not found after visiting all nodes
    return None, float('inf')

# Function to calculate time complexity and print it
def calculate_time_complexity(graph):
    node_count = len(graph)
    edge_count = sum(len(neighbors) for neighbors in graph.values())  # For directed graphs, no division by 2
    print(f"Edge count calculation: {edge_count} (For directed graph, no division by 2)")
    return node_count, edge_count

# Function to read graph and heuristics from a file
def read_input_from_file(filename):
    graph = {}
    heuristics = {}
    start = None
    goal = None
    with open(filename, 'r') as f:
        lines = f.readlines()

        # Reading the graph (adjacency list)
        idx = 0
        while lines[idx].strip() != '':
            node_info = lines[idx].strip().split(":")
            node = node_info[0].strip()
            neighbors = eval(node_info[1].strip())  # Convert string representation of list to actual list
            graph[node] = neighbors
            idx += 1

        # Reading the heuristics
        idx += 1  # Skip the empty line
        while idx < len(lines):
            heuristic_info = lines[idx].strip().split(":")
            node = heuristic_info[0].strip()
            heuristic_value = int(heuristic_info[1].strip())
            heuristics[node] = heuristic_value
            idx += 1

        # Set start and goal (first and last nodes in heuristics)
        start = list(heuristics.keys())[0]
        goal = list(heuristics.keys())[-1]

    return graph, heuristics, start, goal

# Function to write the output to a file
def write_output_to_file(output_filename, path, cost):
    with open(output_filename, 'w') as f:
        if path:
            f.write(f"Path found: {' -> '.join(path)}\n")
            f.write(f"Total cost: {cost}\n")
        else:
            f.write("No path found.\n")

# Read graph, heuristics, start, and goal from file
filename = 'input.txt'  # Replace with your actual filename
graph, heuristics, start, goal = read_input_from_file(filename)

# Run the A* algorithm
path, cost = a_star_search(graph, heuristics, start, goal)

# Write the results to a file
output_filename = 'output.txt'  # Replace with desired output file name
write_output_to_file(output_filename, path, cost)

print(f"Results have been written to {output_filename}.")
