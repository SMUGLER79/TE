#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <iomanip>
using namespace std;

// ----------- Prim's Algorithm (MST with Adjacency Matrix) ------------
class Graph {
    int V;
    vector<vector<int> > adjMatrix;

public:
    Graph(int v) : V(v), adjMatrix(v, vector<int>(v, 0)) {}

    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w; // undirected graph
    }

    void inputGraph() {
        int E;
        cout << "Enter number of edges: ";
        cin >> E;
        cout << "Enter edges (u v weight):\n";
        for (int i = 0; i < E; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            addEdge(u, v, w);
        }
    }

    void printMatrix() {
        cout << "\nAdjacency Matrix:\n    ";
        for (int i = 0; i < V; ++i) cout << setw(4) << i;
        cout << "\n";
        for (int i = 0; i < V; ++i) {
            cout << setw(3) << i << " ";
            for (int j = 0; j < V; ++j)
                cout << setw(4) << adjMatrix[i][j];
            cout << "\n";
        }
    }

    void primMST() {
        vector<int> key(V, INT_MAX), parent(V, -1);
        vector<bool> mstSet(V, false);
        key[0] = 0;

        for (int count = 0; count < V - 1; ++count) {
            int u = -1, minKey = INT_MAX;
            for (int v = 0; v < V; ++v)
                if (!mstSet[v] && key[v] < minKey)
                    minKey = key[v], u = v;

            mstSet[u] = true;

            for (int v = 0; v < V; ++v)
                if (adjMatrix[u][v] && !mstSet[v] && adjMatrix[u][v] < key[v])
                    key[v] = adjMatrix[u][v], parent[v] = u;
        }

        cout << "\nMinimum Spanning Tree (Prim's):\n";
        int totalWeight = 0;
        for (int i = 1; i < V; ++i) {
            cout << parent[i] << " - " << i << " : " << adjMatrix[i][parent[i]] << "\n";
            totalWeight += adjMatrix[i][parent[i]];
        }
        cout << "Total Weight: " << totalWeight << "\n";
    }
};

// ----------- Job Scheduling Problem (Greedy) ------------
struct Job {
    int id;
    int deadline;
    int profit;
};

bool jobComparator(Job a, Job b) {
    return a.profit > b.profit;
}

void jobScheduling() {
    int n;
    cout << "\nEnter number of jobs: ";
    cin >> n;
    vector<Job> jobs(n);

    cout << "Enter jobs (id deadline profit):\n";
    for (int i = 0; i < n; ++i) {
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
    }

    sort(jobs.begin(), jobs.end(), jobComparator);

    int maxDeadline = 0;
    for (int i = 0; i < n; ++i)
        maxDeadline = max(maxDeadline, jobs[i].deadline);

    vector<int> schedule(maxDeadline + 1, -1);
    int totalProfit = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = jobs[i].deadline; j > 0; --j) {
            if (schedule[j] == -1) {
                schedule[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    cout << "\nJob Scheduling Result (Greedy):\n";
    for (int i = 1; i <= maxDeadline; ++i) {
        if (schedule[i] != -1)
            cout << "Time Slot " << i << " -> Job ID " << schedule[i] << "\n";
    }
    cout << "Total Profit: " << totalProfit << "\n";
}

// ----------- Selection Sort ------------
void selectionSort() {
    int n;
    cout << "\nEnter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j)
            if (arr[j] < arr[minIndex])
                minIndex = j;

        if (minIndex != i)
            swap(arr[i], arr[minIndex]);
    }

    cout << "Sorted Array (Selection Sort):\n";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

// ---------------- Menu-Driven Interface ----------------
int main() {
    Graph* g = NULL;
    int choice;

    do {
        cout << "\n===== Greedy Algorithms Menu =====\n";
        cout << "1. Create Graph (for Prim's MST)\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. Find Minimum Spanning Tree (Prim's)\n";
        cout << "4. Solve Job Scheduling Problem\n";
        cout << "5. Exit\n";
        cout << "6. Perform Selection Sort\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int V;
            cout << "Enter number of vertices: ";
            cin >> V;
            g = new Graph(V);
            g->inputGraph();
            break;
        }
        case 2:
            if (g) g->printMatrix();
            else cout << "Create a graph first!\n";
            break;
        case 3:
            if (g) g->primMST();
            else cout << "Create a graph first!\n";
            break;
        case 4:
            jobScheduling();
            break;
        case 5:
            cout << "Exiting program.\n";
            break;
        case 6:
            selectionSort();
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    delete g;
    return 0;
}
