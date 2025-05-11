from heapq import heappush, heappop

def print_board(b):
    for r in b:
        print(" ".join("1" if i==r else "0" for i in range(len(b))))
    print("="*18)

def is_safe(b, r, c):
    return all(c!=b[i] and abs(b[i]-c)!=r-i for i in range(r))

def backtrack(b, r, N, sols, lim):
    if len(sols) >= lim: return
    if r == N:
        sols.append(b[:])
        print_board(b); return
    for c in range(N):
        if is_safe(b, r, c):
            b[r]=c; backtrack(b, r+1, N, sols, lim); b[r]=-1

def conflict(b):
    return sum(b[i]==b[j] or abs(b[i]-b[j])==j-i 
               for i in range(len(b)) 
               for j in range(i+1,len(b)) if b[i]!=-1 and b[j]!=-1)

def branch_bound(N, lim):
    b = [-1]*N; q = [(conflict(b), b)]
    sols = []
    while q and len(sols) < lim:
        _, curr = heappop(q)
        r = next((i for i,x in enumerate(curr) if x==-1), N)
        if r==N: sols.append(curr); print_board(curr); continue
        for c in range(N):
            if is_safe(curr, r, c):
                n = curr[:]; n[r]=c
                heappush(q, (conflict(n), n))

def menu():
    while True:
        print("\n1. Backtracking\n2. Branch & Bound\n3. Exit")
        ch = input("Choose: ")
        if ch == '3': break
        N = int(input("N: "))
        k = int(input("Solutions: "))
        if ch == '1': backtrack([-1]*N, 0, N, [], k)
        elif ch == '2': branch_bound(N, k)
        else: print("Invalid.")

if __name__ == "__main__": menu()