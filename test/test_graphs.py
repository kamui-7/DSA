import pytest
from pprint import pprint
from graphs import *


@pytest.fixture
def adjlist():
    return {1: [2, 3], 2: [4, 5],
            3: [5], 4: [6], 5: [6],
            6: [7], 7: []}


@pytest.fixture
def adjmatrix(adjlist):
    matrix = [
        [0 for i in range(8)]
        for j in range(8)
    ]
    for i in range(1, 8):
        for j in adjlist[i]:
            matrix[i][j] = 1
    return matrix


def test_dfs_recursive_adjlist(capfd, adjlist):
    dfs_rec(adjlist, 1)
    out, err = capfd.readouterr()
    assert out == "1246753"


def test_dfs_iterative_adjlist(capfd, adjlist):
    dfs_iter(adjlist, 1)
    out, err = capfd.readouterr()
    assert out == "1356724"


def test_bfs_adjlist(capfd, adjlist):
    bfs(adjlist, 1)
    out, err = capfd.readouterr()
    assert out == "1234567"


def test_dfs_recursive_adjmatrix(capfd, adjmatrix):
    dfs_rec(adjmatrix, 1, [], matrix_get_neighbors)
    out, err = capfd.readouterr()
    assert out == "1246753"


def test_dfs_iterative_adjmatrix(capfd, adjmatrix):
    dfs_iter(adjmatrix, 1, matrix_get_neighbors)
    out, err = capfd.readouterr()
    assert out == "1356724"


def test_bfs_adjmatrix(capfd, adjmatrix):
    bfs(adjmatrix, 1, matrix_get_neighbors)
    out, err = capfd.readouterr()
    assert out == "1234567"


def test_dijkstra():
    graph = {
        0: [Node(6, 2), Node(2, 1)],
        1: [Node(5, 3)],
        2: [Node(8, 3)],
        3: [Node(15, 5), Node(10, 4)],
        4: [Node(6, 5), Node(2, 6)],
        5: [Node(6, 4), Node(6, 6)],
        6: []
    }
    path = dijkstra(graph, 0, 6)


def test_mst():
    graph = {
        0: [Node(10, 1), Node(1, 2), Node(4, 3)],
        1: [Node(10, 0), Node(3, 2), Node(0, 4)],
        2: [Node(1, 0), Node(3, 1), Node(2, 3), Node(8, 5)],
        3: [Node(4, 0), Node(7, 6), Node(2, 2), Node(2, 5)],
        4: [Node(0, 1), Node(1, 5), Node(8, 7)],
        5: [Node(1, 4), Node(8, 2), Node(9, 7), Node(6, 6), Node(2, 3)],
        6: [Node(7, 3), Node(6, 5), Node(12, 7)],
        7: [Node(8, 4), Node(9, 5), Node(12, 6)]
    }
    assert mst(graph, 0) == 20


def test_detect_cycle():
    graph = {
        0: [1, 2],
        1: [2],
        2: [0, 3],
        3: [3]
    }

    assert check_for_cycle(graph)


def test_topological_order():
    graph = {
        0: [],
        1: [],
        2: [3],
        3: [1],
        4: [0, 1],
        5: [2, 0]
    }
    assert top_sort(graph) == [5, 4, 2, 3, 1, 0]
