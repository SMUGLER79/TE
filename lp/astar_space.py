import heapq

# Object class representing each object (with width, height, and position)
class Object:
    def __init__(self, id, width, height):
        self.id = id
        self.width = width
        self.height = height
        self.x = -1  # x-coordinate for placement
        self.y = -1  # y-coordinate for placement

    def __repr__(self):
        return f"Object{id: {self.id}, width: {self.width}, height: {self.height}, position: ({self.x}, {self.y})}"

# A* Search Node (State)
class Node:
    def __init__(self, objects, cost, heuristic, parent=None):
        self.objects = objects  # Current object placements
        self.cost = cost  # Cost to reach this state (e.g., wasted space)
        self.heuristic = heuristic  # Estimated cost to goal (unused space)
        self.parent = parent  # Parent node in the search tree

    def __lt__(self, other):
        return (self.cost + self.heuristic) < (other.cost + other.heuristic)

# Heuristic function to estimate unused space (minimize empty space in the room)
def calculate_heuristic(room_width, room_height, objects):
    used_area = 0
    for obj in objects:
        if obj.x != -1 and obj.y != -1:  # If the object is placed
            used_area += obj.width * obj.height
    total_area = room_width * room_height
    return total_area - used_area  # Heuristic: empty space in the room

# Check if an object can be placed in a position without overlap
def is_valid_placement(room_width, room_height, objects, obj, x, y):
    # Ensure the object is within the room bounds
    if x + obj.width > room_width or y + obj.height > room_height:
        return False
    # Ensure there is no overlap with other objects
    for other in objects:
        if other.x != -1 and other.y != -1:  # If the object is placed
            if not (x + obj.width <= other.x or x >= other.x + other.width or
                    y + obj.height <= other.y or y >= other.y + other.height):
                return False
    return True

# A* algorithm to arrange objects in the room
def a_star_placement(room_width, room_height, objects):
    initial_cost = 0
    heuristic = calculate_heuristic(room_width, room_height, objects)  # Initial heuristic value
    start_node = Node(objects, initial_cost, heuristic)

    # Priority Queue for A* Search (using heapq)
    open_list = []
    heapq.heappush(open_list, start_node)
    
    # Set to track visited states (we use the placement positions as a unique state identifier)
    visited = set()

    while open_list:
        current_node = heapq.heappop(open_list)

        # Check if the solution is found (all objects are placed)
        if all(obj.x != -1 and obj.y != -1 for obj in current_node.objects):
            return current_node.objects  # Return the solution (final arrangement)

        # Generate new possible states by trying to place each object in different positions
        for obj in current_node.objects:
            if obj.x == -1 and obj.y == -1:  # If the object is not yet placed
                for x in range(room_width):
                    for y in range(room_height):
                        if is_valid_placement(room_width, room_height, current_node.objects, obj, x, y):
                            # Place the object
                            new_objects = [o if o != obj else Object(obj.id, obj.width, obj.height) for o in current_node.objects]
                            new_objects[obj.id].x = x
                            new_objects[obj.id].y = y
                            new_cost = current_node.cost + calculate_heuristic(room_width, room_height, new_objects)
                            new_heuristic = calculate_heuristic(room_width, room_height, new_objects)
                            new_node = Node(new_objects, new_cost, new_heuristic, current_node)

                            # Avoid revisiting the same state
                            state = tuple((o.x, o.y) for o in new_objects)
                            if state not in visited:
                                visited.add(state)
                                heapq.heappush(open_list, new_node)

    return None  # No solution found

# Main function to test the A* arrangement
def main():
    # Room dimensions (e.g., 10x10 grid)
    room_width = 10
    room_height = 10

    # List of objects with their dimensions (width, height)
    objects = [
        Object(0, 3, 2),  # Rectangular object (width=3, height=2)
        Object(1, 4, 2),  # Rectangular object (width=4, height=2)
        Object(2, 2, 4),  # Rectangular object (width=2, height=4)
        Object(3, 2, 2),  # Square object (2x2)
        Object(4, 2, 2),  # Square object (2x2)
        Object(5, 3, 3),  # Square object (3x3)
        Object(6, 3, 3),  # Square object (3x3)
        Object(7, 4, 1),  # Rectangular object (width=4, height=1)
        Object(8, 2, 3),  # Rectangular object (width=2, height=3)
        Object(9, 1, 5)   # Rectangular object (width=1, height=5)
    ]

    # Run the A* algorithm to find the optimal placement of objects
    result = a_star_placement(room_width, room_height, objects)

    if result:
        print("Optimal Arrangement Found:")
        for obj in result:
            print(f"Object {obj.id} placed at ({obj.x}, {obj.y})")
    else:
        print("No solution found.")

if __name__ == "__main__":
    main()



Enter room width: 10
Enter room height: 10
Enter dimensions of objects (object id, width, height):
Width of Object 0: 3
Height of Object 0: 2
Width of Object 1: 4
Height of Object 1: 2
Width of Object 2: 2
Height of Object 2: 4
Width of Object 3: 2
Height of Object 3: 2
Width of Object 4: 2
Height of Object 4: 2
Width of Object 5: 3
Height of Object 5: 3
Width of Object 6: 3
Height of Object 6: 3
Width of Object 7: 4
Height of Object 7: 1
Width of Object 8: 2
Height of Object 8: 3
Width of Object 9: 1
Height of Object 9: 5

Initial empty room layout:
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0

Updated room layout:
1 1 0 0 0 0 0 0 0 0
1 1 0 0 0 0 0 0 0 0
0 0 0 2 2 0 0 0 0 0
0 0 0 2 2 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
