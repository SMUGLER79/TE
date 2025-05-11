#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int V; // Number of vertices
vector<vector<int>> graph;
int solutionCount = 0;

// Check if color assignment is safe
bool isSafe(int v, const vector<int>& color, int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && color[i] == c)
            return false;
    return true;
}

// Backtracking algorithm
void graphColoringBT(vector<int>& color, int v, int m) {
    if (v == V) {
        cout << "\nSolution " << ++solutionCount << ": ";
        for (int i = 0; i < V; i++)
            cout << color[i] << " ";
        cout << endl;
        return;
    }

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, color, c)) {
            color[v] = c;
            graphColoringBT(color, v + 1, m);
            color[v] = 0;
        }
    }
}

// Branch & Bound (here: same as Backtracking, but can be optimized with pruning)
void graphColoringBB(vector<int>& color, int v, int m, vector<int>& degreeOrder) {
    if (v == V) {
        cout << "\nSolution " << ++solutionCount << ": ";
        for (int i = 0; i < V; i++)
            cout << color[degreeOrder[i]] << " ";
        cout << endl;
        return;
    }

    int node = degreeOrder[v];

    for (int c = 1; c <= m; c++) {
        if (isSafe(node, color, c)) {
            color[node] = c;
            graphColoringBB(color, v + 1, m, degreeOrder);
            color[node] = 0;
        }
    }
}

// Degree-based ordering (for BnB)
vector<int> getDegreeOrdering() {
    vector<pair<int, int>> deg(V);
    for (int i = 0; i < V; i++) {
        int count = 0;
        for (int j = 0; j < V; j++)
            if (graph[i][j]) count++;
        deg[i] = {count, i};
    }

    sort(deg.rbegin(), deg.rend()); // Higher degree first
    vector<int> order(V);
    for (int i = 0; i < V; i++)
        order[i] = deg[i].second;

    return order;
}

int main() {
    int m, choice;
    cout << "Enter number of vertices in the graph: ";
    cin >> V;

    graph.resize(V, vector<int>(V));
    cout << "Enter adjacency matrix (0 or 1):\n";
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            cin >> graph[i][j];

    cout << "Enter number of colors: ";
    cin >> m;

    do {
        cout << "\n--- Graph Coloring CSP Solver ---\n";
        cout << "1. Solve using Backtracking\n";
        cout << "2. Solve using Branch & Bound\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        vector<int> color(V, 0);
        solutionCount = 0;

        if (choice == 1) {
            cout << "\nSolving using Backtracking...\n";
            graphColoringBT(color, 0, m);
            if (solutionCount == 0)
                cout << "No solution found.\n";
        }
        else if (choice == 2) {
            cout << "\nSolving using Branch & Bound (with degree heuristic)...\n";
            vector<int> degreeOrder = getDegreeOrdering();
            graphColoringBB(color, 0, m, degreeOrder);
            if (solutionCount == 0)
                cout << "No solution found.\n";
        }
    } while (choice != 3);

    cout << "Program exited.\n";
    return 0;
}