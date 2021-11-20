#include <stdbool.h>

#define CAPACITY 1000

struct MaxHeap {
    int size;
    int capacity;
    int data[CAPACITY];
};

int heap_get_max(struct MaxHeap *heap);
void heap_insert(struct MaxHeap *heap, int key);
void insert_rec(struct MaxHeap *heap, int indx);
void sift_up(struct MaxHeap *heap, int indx, int parent_indx);
