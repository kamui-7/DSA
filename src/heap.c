#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "heap.h"

int heap_len(struct MaxHeap *heap) { return heap->size; }

bool heap_is_empty(struct MaxHeap *heap) { return heap->size == 0; }

int heap_get_max(struct MaxHeap *heap) { return heap->data[0]; }

int heap_extract_max(struct MaxHeap *heap) {
    int max_item = heap_get_max(heap);
    heap_remove(heap, 0);
    return max_item;
}

void swap_arr(int arr[], int indx, int parent_indx) {
    int temp = arr[parent_indx];
    arr[parent_indx] = arr[indx];
    arr[indx] = temp;
}

static void remove_rec(struct MaxHeap *heap, int indx) {
    int child_left = 2 * indx + 1;
    int child_right = 2 * indx + 2;

    if (heap->data[indx] >= heap->data[child_left] &&
        heap->data[indx] >= heap->data[child_right]) {
        return;
    }

    int larger_child = MIN(child_left, child_right);

    swap_arr(heap->data, larger_child, indx);
    remove_rec(heap, larger_child);
}

static void insert_rec(struct MaxHeap *heap, int indx) {
    int parent = (indx - 1) / 2;

    if (parent < 0) {
        return;
    }

    // met base case
    if (heap->data[parent] >= heap->data[indx]) {
        return;
    }

    swap_arr(heap->data, indx, parent);
    insert_rec(heap, parent);
}

void heap_insert(struct MaxHeap *heap, int key) {
    if (heap->size == heap->capacity) {
        printf("Max capacity reached");
        exit(1);
        return;
    }

    int indx = heap->size;
    heap->data[indx] = key;
    heap->size++;

    if (heap->size == 1) {
        return;
    }

    insert_rec(heap, indx);
}

void heap_remove(struct MaxHeap *heap, int indx) {
    swap_arr(heap->data, heap->size - 1, indx);
    heap->data[heap->size - 1] = 0;
    heap->size--;
    remove_rec(heap, indx);
}

void heapify(int arr[], int indx, int size) {
    int child_left = 2 * indx + 1;
    int child_right = 2 * indx + 2;

    if (child_left >= size || child_right >= size) {
        return;
    }

    if (arr[indx] >= arr[child_left] && arr[indx] >= arr[child_right]) {
        return;
    }

    int larger_child;

    if (arr[child_left] > arr[child_right]) {
        larger_child = child_left;
    } else {
        larger_child = child_right;
    }

    swap_arr(arr, larger_child, indx);
    heapify(arr, larger_child, size);
}

void heap_sort(int arr[], int size) {
    int csize = size;

    while (csize > 0) {
        heapify(arr, 0, csize);
        swap_arr(arr, 0, csize - 1);
        csize--;
    }
}
