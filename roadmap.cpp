class UnionFind:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        root_u = self.find(u)
        root_v = self.find(v)
        
        if root_u != root_v:
            if self.rank[root_u] > self.rank[root_v]:
                self.parent[root_v] = root_u
            elif self.rank[root_u] < self.rank[root_v]:
                self.parent[root_u] = root_v
            else:
                self.parent[root_v] = root_u
                self.rank[root_u] += 1

def kruskal(n, edges):
    # Sorting edges based on their cost
    edges.sort(key=lambda x: x[2])
    
    uf = UnionFind(n + 1)
    total_cost = 0
    edge_count = 0
    
    for u, v, cost in edges:
        if uf.find(u) != uf.find(v):
            uf.union(u, v)
            total_cost += cost
            edge_count += 1
            if edge_count == n - 1:
                break
    
    if edge_count == n - 1:
        return total_cost
    else:
        return "IMPOSSIBLE"

def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    
    n = int(data[0])
    m = int(data[1])
    
    edges = []
    index = 2
    for _ in range(m):
        a = int(data[index])
        b = int(data[index+1])
        c = int(data[index+2])
        edges.append((a, b, c))
        index += 3
    
    result = kruskal(n, edges)
    print(result)

