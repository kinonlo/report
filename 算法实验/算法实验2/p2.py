INF = float('inf')

def floyd_warshall(graph):
    n = len(graph)
    dist = list(map(lambda i : list(map(lambda j : j , i)) , graph))
    next_hop = [[0 if i == j else j for j in range(n)] for i in range(n)]

    for k in range(n):
        for i in range(n):
            for j in range(n):
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
                    next_hop[i][j] = next_hop[i][k]

    return dist, next_hop

def get_path(u, v, next_hop):
    path = [u]
    while u != v:
        u = next_hop[u][v]
        path.append(u)
    path = list(map(lambda x : x+1, path))
    return path

graph = [
    [0, 3, 8, INF,-4],
    [INF, 0, INF, 1,7],
    [INF,4,0,INF,INF],
    [2,INF,-5,0,INF],
    [INF,INF,INF,60,0]
]

distances, next_hops = floyd_warshall(graph)

print("最短路径长度:")
for row in distances:
    print(row)

print("\n最短路径:")
for i in range(len(graph)):
    for j in range(len(graph)):
        if i != j:
            print(f" {i+1} 到 {j+1}: {get_path(i, j, next_hops)}")
