#%%
#adjacency list
graph_dict = {
    0:[1,2],
    1:[2,3],
    2:[3],
    3:[4],
    4:[0,1,5],
    5:[]
}

party = {
    0:[1,2],
    1:[0,2],
    2:[0,1],
    3:[4],
    4:[3]
}

def find_path(target):
    if target not in visited:
        print("No path")
    else:
        path = []
        while target != -1:
            path.append(target)
            target = parents[target]
        print(*reversed(path))

# %%
#BFS
from collections import deque
source = 0
visited = set([source])
counter = 0
def bfs(graph, source):
    queue = deque([source])
    parents = dict.fromkeys(graph.keys())
    distance = dict.fromkeys(graph.keys(), 0)
    parents[source] = -1
    visited.add(source)
    while(queue):
        cur = queue.popleft()
        for adj in graph[cur]:
            if adj not in visited:
                visited.add(adj)
                queue.append(adj)
                parents[adj] = cur
                distance[adj] = distance[cur] + 1
                # print(adj, distance[adj]) 

#find_path(5)
#%%
#Party problem
visited = set()
for node in party.keys():
    print(visited)
    if node not in visited:
        bfs(party, node)
        counter += 1
print(counter)
#

# %%
#DFS
