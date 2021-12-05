from sort import *
import pytest


def test_merge_sort():
    list = [3, 51, 33, 0, 98, 12]
    srted = sorted(list)
    assert merge_sort(list) == srted


def test_insertion_sort():
    list = [3, 51, 33, 0, 98, 12]
    insertion_sort(list)
    srted = sorted(list)
    assert list == srted


def test_bubble_sort():
    list = [3, 51, 33, 0, 98, 12]
    bubble_sort(list)
    srted = sorted(list)
    assert list == srted


def test_selection_sort():
    list = [3, 51, 33, 0, 98, 12]
    selection_sort(list)
    srted = sorted(list)
    assert list == srted


def test_quick_sort():
    list = [10, 16, 8, 12, 15, 6, 3, 9, 5]
    quick_sort(list)
    srted = sorted(list)
    assert list == srted
