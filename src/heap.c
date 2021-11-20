#include "heap.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int heap_get_max(struct MaxHeap *heap) { return heap->data[0]; }

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

void insert_rec(struct MaxHeap *heap, int indx) {
    int parent = (indx - 1) / 2;

    if (parent < 0) {
        return;
    }

    // met base case
    if (heap->data[parent] >= heap->data[indx]) {
        return;
    }

    sift_up(heap, indx, parent);
    insert_rec(heap, parent);
}

void sift_up(struct MaxHeap *heap, int indx, int parent_indx) {
    int temp = heap->data[parent_indx];
    heap->data[parent_indx] = heap->data[indx];
    heap->data[indx] = temp;
}
