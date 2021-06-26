#include <stdbool.h>

struct Array {
    int *ptr;
    int len;
    int capacity;
};

void resize(struct Array *arr, int new_size);
void set(struct Array *arr, int indx, int item);
void print_array(struct Array *arr);
void push(struct Array *arr, int item);
int find(struct Array *arr, int key);
bool is_empty(struct Array *arr);
int at(struct Array *arr, int indx);
int pop(struct Array *arr);
void insert(struct Array *arr, int indx, int item);
void prepend(struct Array *arr, int item);
void erase(struct Array *arr, int indx);
void remove_itm(struct Array *arr, int item);
