#include "array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void resize(struct Array *arr, int new_size) {
    arr->ptr = (int *)realloc(arr->ptr, sizeof(int) * new_size);
    arr->capacity = new_size;
}

void set(struct Array *arr, int indx, int item) { *(arr->ptr + indx) = item; }

void array_print(struct Array *arr) {
    for (int i = 0; i < arr->len; i++) {
        printf("%d ", *(arr->ptr + i));
    }
    printf("\n");
}

void array_push(struct Array *arr, int item) {
    if (arr->len == arr->capacity) {
        resize(arr, arr->capacity * 2);
    }

    *(arr->ptr + arr->len) = item;
    arr->len++;
}

int array_find(struct Array *arr, int key) {
    for (int i = 0; i < arr->len; i++) {
        if (*(arr->ptr + i) == key) {
            return i;
        }
    }
    return -1;
}

bool array_empty(struct Array *arr) { return arr->len == 0; }

int array_at(struct Array *arr, int indx) { return *(arr->ptr + indx); }

int array_pop(struct Array *arr) {
    if (arr->len == (arr->capacity) / 4) {
        resize(arr, arr->capacity / 2);
    }

    int last_idx = arr->len - 1;
    int last = *arr->ptr + last_idx;

    *(arr->ptr + last_idx) = 0;
    arr->len -= 1;

    return last;
}

void array_insert(struct Array *arr, int indx, int item) {
    if (arr->len == arr->capacity) {
        resize(arr, arr->capacity * 2);
    }

    for (int i = arr->len - 1; i >= indx; i--) {
        set(arr, i + 1, array_at(arr, i));
        set(arr, i, 0);
    }

    set(arr, indx, item);
    arr->len++;
}

void array_prepend(struct Array *arr, int item) { array_insert(arr, 0, item); }

void array_erase(struct Array *arr, int indx) {
    if (arr->len == (arr->capacity) / 4) {
        resize(arr, arr->capacity / 2);
    }

    set(arr, indx, 0);
    for (int i = indx + 1; i < arr->len; i++) {
        set(arr, i - 1, array_at(arr, i));
        set(arr, i, 0);
    }
    arr->len--;
}

void array_remove(struct Array *arr, int item) {
    for (int i = 0; i < arr->len; i++) {
        if (*(arr->ptr + i) == item) {
            array_erase(arr, i);
        }
    }
}
