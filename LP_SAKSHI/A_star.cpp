#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <climits>
#include <functional> // 🔧 Needed for std::function

using namespace std;

struct Node {
    int x, y;
    int g, h; // g = cost from start, h = heuristic
    Node* parent;

    Node(int x, int y, int g, int h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}

    int f() const {
        return g + h;
    }
};

struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->f() > b->f(); // min-heap based on f = g + h
    }
};

int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool isValid(int x, int y, int rows, int cols, const vector<vector<int>>& grid) {
    return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0;
}

void printPath(Node* node) {
    stack<pair<int, int>> path;
    while (node) {
        path.push({node->x, node->y});
        node = node->parent;
    }

    cout << "Path (start to goal):\n";
    while (!path.empty()) {
        auto [x, y] = path.top();
        path.pop();
        cout << "(" << x << ", " << y << ")";
        if (!path.empty()) cout << " -> ";
    }
    cout << endl;
}

void aStarSearch(vector<vector<int>>& grid, int sx, int sy, int gx, int gy) {
    int rows = grid.size();
    int cols = grid[0].size();

    priority_queue<Node*, vector<Node*>, CompareNode> open; // 🔧 Fixed comparator
    vector<vector<bool>> closed(rows, vector<bool>(cols, false));

    Node* start = new Node(sx, sy, 0, manhattan(sx, sy, gx, gy));
    open.push(start);

    vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}}; // up, down, left, right

    while (!open.empty()) {
        Node* current = open.top();
        open.pop();

        if (closed[current->x][current->y]) continue;
        closed[current->x][current->y] = true;

        if (current->x == gx && current->y == gy) {
            printPath(current);
            return;
        }

        for (auto [dx, dy] : directions) {
            int nx = current->x + dx;
            int ny = current->y + dy;

            if (isValid(nx, ny, rows, cols, grid) && !closed[nx][ny]) {
                int gNew = current->g + 1;
                int hNew = manhattan(nx, ny, gx, gy);
                open.push(new Node(nx, ny, gNew, hNew, current));
            }
        }
    }

    cout << "No path found from start to goal.\n";
}

int main() {
    int rows, cols;
    cout << "Enter grid size (rows cols): ";
    cin >> rows >> cols;

    vector<vector<int>> grid(rows, vector<int>(cols, 0));

    int numWalls;
    cout << "Enter number of walls: ";
    cin >> numWalls;

    cout << "Enter wall positions (x y):\n";
    for (int i = 0; i < numWalls; ++i) {
        int wx, wy;
        cin >> wx >> wy;
        if (wx >= 0 && wx < rows && wy >= 0 && wy < cols)
            grid[wx][wy] = 1;
    }

    int sx, sy, gx, gy;
    cout << "Enter start position (x y): ";
    cin >> sx >> sy;
    cout << "Enter goal position (x y): ";
    cin >> gx >> gy;

    if (!isValid(sx, sy, rows, cols, grid) || !isValid(gx, gy, rows, cols, grid)) {
        cout << "Invalid start or goal position.\n";
        return 1;
    }

    while (true) {
        cout << "\n--- A* Pathfinding Menu ---\n";
        cout << "1. Run A* Search\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                aStarSearch(grid, sx, sy, gx, gy);
                break;
            case 2:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}