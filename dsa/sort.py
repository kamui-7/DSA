import sys


def swap(array, i, j):
    temp = array[i]
    array[i] = array[j]
    array[j] = temp


def merge_sort(array):
    length = len(array)
    if length == 1:
        return array

    m = length // 2
    left = merge_sort(array[:m])
    right = merge_sort(array[m:])
    return merge(left, right)


def merge(left, right):
    output = []
    i = j = 0

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            output.append(left[i])
            i += 1
        else:
            output.append(right[j])
            j += 1

    output.extend(left[i:])
    output.extend(right[j:])

    return output


def insertion_sort(array):
    for j in range(1, len(array)):
        key = array[j]
        i = j - 1

        while i >= 0 and array[i] > key:
            array[i+1] = array[i]
            i -= 1
        array[i+1] = key


def bubble_sort(array):
    while True:
        swapped = False
        for i in range(len(array) - 1):
            j = i + 1
            if array[i] > array[j]:
                swap(array, i, j)
                swapped = True

        if not swapped:
            return


def selection_sort(array):
    min = unsorted = 0

    while unsorted != len(array) - 1:
        for i in range(unsorted, len(array)):
            if array[i] < array[min]:
                min = i

        swap(array, min, unsorted)

        unsorted += 1


def quick_sort(array):
    print()
    array.append(sys.maxsize)
    quick_sort_range(array, 0, len(array) - 1)


def quick_sort_range(array, l, h):
    if l < h:
        j = qs_partition(array, l, h)
        quick_sort_range(array, l, j)
        quick_sort_range(array, j+1, h)


def qs_partition(array, l, h):
    pivot = array[l]
    i = l
    j = h

    while i < j:
        while True:
            if array[i] > pivot:
                break
            i += 1

        while True:
            if array[j] <= pivot:
                break
            j -= 1

        if i < j:
            swap(array, i, j)

    swap(array, l, j)

    return j
