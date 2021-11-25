from collections import deque
from pprint import pprint
from dataclasses import dataclass, field
from typing import List, Tuple
import heapq
import sys


def matrix_get_neighbors(graph, indx):
    neighbors = []
    row = graph[indx]
    for i in range(len(row)):
        curr = row[i]
        if curr:
            neighbors.append(i)
    return neighbors


def adjlist_neighbors(graph, point): return graph[point]


def dfs_rec(graph, point, visited=[], get_neighbors=adjlist_neighbors):
    if point not in visited:
        print(point, end="")
        visited.append(point)
        for neighbor in get_neighbors(graph, point):
            dfs_rec(graph, neighbor, visited, get_neighbors)


def dfs_iter(graph, point, get_neighbors=adjlist_neighbors):
    stack = [point]
    visited = []

    while len(stack) > 0:
        curr = stack.pop()
        if curr in visited:
            continue
        print(curr, end="")
        visited.append(curr)
        for neighbor in get_neighbors(graph, curr):
            stack.append(neighbor)


def bfs(graph, point, get_neighbors=adjlist_neighbors):
    queue = deque([point])
    visited = []

    while len(queue) > 0:
        curr = queue.popleft()
        if curr in visited:
            continue
        print(curr, end="")
        visited.append(curr)
        for neighbor in get_neighbors(graph, curr):
            queue.append(neighbor)


@dataclass(order=True)
class Node:
    weight: int
    data: int = field(compare=False)


@dataclass
class DistanceEntry:
    dist: int
    prev: Node


def dijkstra(graph, start, end) -> List[int]:
    visited = []
    unvisited = [Node(0, start)]
    distances = {k: DistanceEntry(sys.maxsize, None) for k in graph.keys()}
    distances[start].dist = 0

    while len(unvisited) > 0:
        curr = heapq.heappop(unvisited)

        neighbors = graph[curr.data]
        if neighbors:
            closest = neighbors[0]
            closest_num = distances[neighbors[0].data].dist

            for neighbor in neighbors:
                new_cost = distances[curr.data].dist + neighbor.weight
                old_cost = distances[neighbor.data].dist
                entry = DistanceEntry(min(old_cost, new_cost), curr)
                distances[neighbor.data] = entry

                if entry.dist < closest_num:
                    closest = neighbor
                    closest_num = entry.dist

            if closest in visited:
                continue

            heapq.heappush(unvisited, closest)

        visited.append(curr)

    return path_from_dist(distances, end)


def path_from_dist(distances, end):
    path = [end]
    via_node = distances[end]
    while via_node is not None:
        prev = via_node.prev
        if prev:
            path.insert(0, prev.data)
            via_node = distances.get(prev.data)
        else:
            via_node = None

    return path


@dataclass(order=True)
class Edge:
    start: int = field(compare=False)
    end: int = field(compare=False)
    cost: int


# minimum spanning tree
# returns cost
def mst(graph, start) -> int:
    print()
    n = len(graph.keys())
    m = n - 1
    # priority queue that sorts edges based on min cost
    edges = []
    visited = []
    mst = []
    cost = 0

    def add_edges(node):
        visited.append(node)
        for neighbor in graph[node]:
            if neighbor not in visited:
                heapq.heappush(edges, Edge(
                    node, neighbor.data, neighbor.weight))

    add_edges(start)

    while len(edges) > 0 and len(mst) != m:
        curr = heapq.heappop(edges)
        if curr.end in visited:
            continue

        cost += curr.cost
        mst.append(curr)
        add_edges(curr.end)

    return cost


def check_for_cycle(graph) -> bool:
    return False


def top_dfs(graph, node, visited, top_order):
    visited.append(node)
    for neighbor in graph[node]:
        if neighbor not in visited:
            top_dfs(graph, neighbor, visited, top_order)

    top_order.append(node)


def top_sort(graph):
    if check_for_cycle(graph):
        return

    top_order = []  # stack
    visited = []

    for i in graph.keys():
        if i not in visited:
            top_dfs(graph, i, visited, top_order)

    return list(reversed(top_order))


def count_connected(graph):
    pass


def list_strongly_connected(graph):
    pass


def check_bipartite(graph):
    pass
