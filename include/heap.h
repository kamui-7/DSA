#include <stdbool.h>

#define CAPACITY 1000

struct MaxHeap {
    int size;
    int capacity;
    int data[CAPACITY];
};

int heap_get_max(struct MaxHeap *heap);
void heap_insert(struct MaxHeap *heap, int key);
void heap_swap(struct MaxHeap *heap, int indx, int parent_indx);
void heap_remove(struct MaxHeap *heap, int indx);
int heap_len(struct MaxHeap *heap);
bool heap_is_empty(struct MaxHeap *heap);
int heap_extract_max(struct MaxHeap *heap);
void heapify(int arr[], int indx, int size);
void heap_sort(int arr[], int size);
