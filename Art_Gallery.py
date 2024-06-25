from collections import defaultdict, deque

def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    
    N = int(data[0])
    M = int(data[1])
    K = int(data[2])
    
    graph = defaultdict(list)
    
    index = 3
    for _ in range(M):
        a = int(data[index])
        b = int(data[index + 1])
        graph[a].append(b)
        graph[b].append(a)
        index += 2
    
    guards = []
    for i in range(K):
        p_i = int(data[index])
        h_i = int(data[index + 1])
        guards.append((p_i, h_i))
        index += 2
    
    guarded = [False] * (N + 1)
    
    for p_i, h_i in guards:
        visited = [False] * (N + 1)
        queue = deque([(p_i, 0)])
        visited[p_i] = True
        
        while queue:
            current, dist = queue.popleft()
            
            if dist > h_i:
                continue
            
            guarded[current] = True
            
            for neighbor in graph[current]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    queue.append((neighbor, dist + 1))
    
    result = []
    for v in range(1, N + 1):
        if guarded[v]:
            result.append(v)
    
    print(len(result))
    if result:
        print(" ".join(map(str, result)))

if __name__ == "__main__":
    main()

