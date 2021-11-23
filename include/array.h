#include <stdbool.h>

struct Array {
    int *ptr;
    int len;
    int capacity;
};

void array_print(struct Array *arr);
void array_push(struct Array *arr, int item);
int array_find(struct Array *arr, int key);
bool array_empty(struct Array *arr);
int array_at(struct Array *arr, int indx);
int array_pop(struct Array *arr);
void array_insert(struct Array *arr, int indx, int item);
void array_prepend(struct Array *arr, int item);
void array_erase(struct Array *arr, int indx);
void array_remove(struct Array *arr, int item);
