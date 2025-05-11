from collections import deque

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.adj = [[] for _ in range(vertices)]

    def add_edge(self, u, v):
        self.adj[u].append(v)
        self.adj[v].append(u)

    def dfs_search(self, target):
        visited = [False] * self.V
        found = [False]

        def dfs(v, level):
            if found[0]: return
            visited[v] = True
            print(f"DFS -> Visited {v} at level {level}")
            if v == target:
                print(f"Target {target} found at level {level} using DFS!\n")
                found[0] = True
                return
            for neighbor in self.adj[v]:
                if not visited[neighbor]:
                    dfs(neighbor, level + 1)

        for i in range(self.V):
            if not visited[i]:
                dfs(i, 0)
                if found[0]: break
        if not found[0]:
            print(f"Target {target} not found in graph using DFS.\n")

    def bfs_search(self, target):
        visited = [False] * self.V
        found = False

        for i in range(self.V):
            if not visited[i]:
                queue = deque([(i, 0)])
                visited[i] = True
                while queue:
                    node, level = queue.popleft()
                    print(f"BFS -> Visited {node} at level {level}")
                    if node == target:
                        print(f"Target {target} found at level {level} using BFS!\n")
                        return
                    for neighbor in self.adj[node]:
                        if not visited[neighbor]:
                            visited[neighbor] = True
                            queue.append((neighbor, level + 1))
        print(f"Target {target} not found in graph using BFS.\n")

def main():
    V = int(input("Enter number of vertices: "))
    E = int(input("Enter number of edges: "))
    g = Graph(V)

    print("Enter the edges (e.g., '0 1'):")
    for _ in range(E):
        u, v = map(int, input().split())
        g.add_edge(u, v)

    while True:
        print("\nMenu:")
        print("1. Recursive DFS with Levels")
        print("2. BFS with Levels")
        print("3. Search Target using DFS")
        print("4. Search Target using BFS")
        print("5. Exit")
        choice = input("Enter your choice: ")

        if choice == '1':
            g.dfs_search(target=-1)  # -1 means no target, just traversal
        elif choice == '2':
            g.bfs_search(target=-1)
        elif choice == '3':
            t = int(input("Enter target vertex to search using DFS: "))
            g.dfs_search(target=t)
        elif choice == '4':
            t = int(input("Enter target vertex to search using BFS: "))
            g.bfs_search(target=t)
        elif choice == '5':
            print("Exiting...")
            break
        else:
            print("Invalid choice!")

if __name__ == "__main__":
    main()
