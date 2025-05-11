#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

// Define the object to place in the room
struct Object {
    char id;
    int width;
    int height;
};

// Define the state for the A* search algorithm
struct State {
    vector<vector<char> > room;
    vector<Object> objects;
    int x, y;
    int cost;
    
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

// Check if the object can be placed at the given position
bool canPlace(const vector<vector<char> >& room, const Object& obj, int x, int y) {
    if (x + obj.width > room.size() || y + obj.height > room[0].size()) {
        return false;
    }

    for (int i = 0; i < obj.width; i++) {
        for (int j = 0; j < obj.height; j++) {
            if (room[x + i][y + j] != '.') {
                return false;
            }
        }
    }

    return true;
}

// Place the object in the room
void placeObject(vector<vector<char> >& room, const Object& obj, int x, int y) {
    for (int i = 0; i < obj.width; i++) {
        for (int j = 0; j < obj.height; j++) {
            room[x + i][y + j] = obj.id;
        }
    }
}

// A* search to place all objects in the room
vector<vector<char> > arrangeObjects(int rows, int cols, const vector<Object>& objects) {
    vector<vector<char> > emptyRoom(rows, vector<char>(cols, '.'));
    priority_queue<State, vector<State>, greater<State> > pq;

    State initialState = {emptyRoom, objects, 0, 0, 0};
    pq.push(initialState);

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (current.objects.empty()) {
            return current.room;
        }

        Object obj = current.objects.back();
        vector<Object> remainingObjects = current.objects;
        remainingObjects.pop_back();

        for (int i = 0; i <= rows - obj.width; i++) {
            for (int j = 0; j <= cols - obj.height; j++) {
                if (canPlace(current.room, obj, i, j)) {
                    vector<vector<char> > newRoom = current.room;
                    placeObject(newRoom, obj, i, j);
                    State newState = {newRoom, remainingObjects, i, j, current.cost + 1};
                    pq.push(newState);
                }
            }
        }
    }

    return emptyRoom; // Fallback, should never reach here
}

int main() {
    // Room dimensions
    int rows, cols;
    cout << "Enter room dimensions (rows, columns): ";
    cin >> rows >> cols;

    // Objects to arrange in the room
    int numObjects;
    cout << "Enter number of objects: ";
    cin >> numObjects;

    vector<Object> objects(numObjects);
    for (int i = 0; i < numObjects; i++) {
        cout << "Enter object " << i + 1 << " (id, width, height): ";
        cin >> objects[i].id >> objects[i].width >> objects[i].height;
    }

    // Arrange objects in the room
    vector<vector<char> > room = arrangeObjects(rows, cols, objects);

    // Display the arranged room
    cout << "\nArranged Room: \n";
    for (const auto& row : room) {
        for (char c : row) {
            cout << c << " ";
        }
        cout << endl;
    }

    return 0;
}
