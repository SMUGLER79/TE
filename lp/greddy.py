class Job:
    def __init__(self, id, deadline, profit):
        self.id = id
        self.deadline = deadline
        self.profit = profit

def job_scheduling():
    n = int(input("Enter number of jobs: "))
    jobs = []
    for _ in range(n):
        jid = input("Job ID: ")
        deadline = int(input("Deadline: "))
        profit = int(input("Profit: "))
        jobs.append(Job(jid, deadline, profit))

    jobs.sort(key=lambda x: x.profit, reverse=True)
    max_deadline = max(job.deadline for job in jobs)
    slots = [None] * max_deadline
    total_profit = 0

    for job in jobs:
        for i in range(job.deadline - 1, -1, -1):
            if slots[i] is None:
                slots[i] = job.id
                total_profit += job.profit
                break

    print("\nScheduled Jobs:", [j for j in slots if j])
    print("Total Profit:", total_profit)

# ----- Kruskal's MST -----
class DisjointSet:
    def __init__(self, n):
        self.parent = list(range(n))

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        pu, pv = self.find(u), self.find(v)
        if pu != pv:
            self.parent[pv] = pu
            return True
        return False

def kruskal_mst():
    n = int(input("Enter number of nodes: "))
    m = int(input("Enter number of edges: "))
    edges = []
    print("Enter edges (u v weight):")
    for _ in range(m):
        u, v, w = map(int, input().split())
        edges.append((u, v, w))

    edges.sort(key=lambda x: x[2])
    ds = DisjointSet(n)
    mst, total_cost = [], 0

    for u, v, w in edges:
        if ds.union(u, v):
            mst.append((u, v, w))
            total_cost += w

    print("\nEdges in MST:")
    for u, v, w in mst:
        print(f"{u} -- {v} : {w}")
    print("Total Cost:", total_cost)

# ----- Selection Sort -----
def selection_sort():
    arr = list(map(int, input("Enter elements to sort (space separated): ").split()))
    n = len(arr)
    print("\nPerforming Selection Sort:")
    for i in range(n):
        min_idx = i
        for j in range(i+1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
        print(f"Step {i+1}: {arr}")
    print("Sorted Array:", arr)

# ----- Main Menu -----
def main():
    while True:
        print("\n--- Greedy Algorithms Menu ---")
        print("1. Job Scheduling Problem")
        print("2. Kruskal's MST Algorithm")
        print("3. Selection Sort")
        print("4. Exit")
        choice = input("Enter your choice (1-4): ")

        if choice == '1':
            job_scheduling()
        elif choice == '2':
            kruskal_mst()
        elif choice == '3':
            selection_sort()
        elif choice == '4':
            print("Exiting. Thank you!")
            break
        else:
            print("Invalid choice. Try again.")

if __name__ == "__main__":
    main()
