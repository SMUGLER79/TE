#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    int V; // number of vertices
    vector<vector<int>> adj; // adjacency list

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v); // undirected graph
        adj[v].push_back(u);
    }

    // DFS with levels
    void DFSUtil(int v, vector<bool>& visited, vector<int>& level, int current_level) {
        visited[v] = true;
        level[v] = current_level;
        cout << "Node: " << v << ", Level: " << current_level << endl;

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited, level, current_level + 1);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        vector<int> level(V, -1);
        cout << "DFS traversal with levels starting from vertex " << start << ":\n";
        DFSUtil(start, visited, level, 0);
    }

    // BFS with levels
    void BFS(int start) {
        vector<bool> visited(V, false);
        vector<int> level(V, -1);
        queue<int> q;

        visited[start] = true;
        level[start] = 0;
        q.push(start);

        cout << "BFS traversal with levels starting from vertex " << start << ":\n";

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            cout << "Node: " << curr << ", Level: " << level[curr] << endl;

            for (int neighbor : adj[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    level[neighbor] = level[curr] + 1;
                    q.push(neighbor);
                }
            }
        }
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;
    cout << "Enter edges (u v) where 0 <= u,v < " << V << ":\n";
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    while (true) {
        cout << "\n--- Graph Traversal Menu ---\n";
        cout << "1. Depth First Search (DFS)\n";
        cout << "2. Breadth First Search (BFS)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        int choice, start;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter starting vertex for DFS: ";
                cin >> start;
                g.DFS(start);
                break;
            case 2:
                cout << "Enter starting vertex for BFS: ";
                cin >> start;
                g.BFS(start);
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}