#include <stdbool.h>

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a < b ? b : a
#define CAPACITY 1000

struct MaxHeap {
    int size;
    int capacity;
    int data[CAPACITY];
};

int heap_get_max(struct MaxHeap *heap);
void heap_insert(struct MaxHeap *heap, int key);
void insert_rec(struct MaxHeap *heap, int indx);
void swap(struct MaxHeap *heap, int indx, int parent_indx);
void heap_remove(struct MaxHeap *heap, int indx);
void remove_rec(struct MaxHeap *heap, int indx);
int get_size(struct MaxHeap *heap);
bool heap_is_empty(struct MaxHeap *heap);
int extract_max(struct MaxHeap *heap);
void heapify(int arr[], int indx, int size);
void heapsort(int arr[], int size);
