#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct Array {
    int *ptr;
    int len;
    int capacity;
};

void resize(struct Array* arr, int new_size) {
    arr->ptr = (int*) realloc(arr->ptr, sizeof(int) * new_size);
    arr->capacity = new_size;
}

void set(struct Array* arr, int indx, int item) {
    *(arr->ptr+indx) = item;
}

void print_array(struct Array* arr) {
    for (int i = 0; i < arr->len; i++) {
        printf("%d\n", *(arr->ptr+i));
    }
}

void push(struct Array* arr, int item) {
    if (arr->len == arr->capacity) {
        resize(arr, arr->capacity * 2);
    }

    *(arr->ptr + arr->len) = item;
    arr->len++;
}

int find(struct Array* arr, int key) {
    for (int i = 0; i < arr->len; i++)  {
        if (*(arr->ptr+i) == key) {
            return i;
        }
    }
    return -1;
}

bool is_empty(struct Array* arr) {
    return arr->len == 0;
}

int at(struct Array* arr, int indx) {
    return *(arr->ptr+indx);
}

int pop(struct Array* arr) {
    if (arr->len == (arr->capacity)/4) {
        resize(arr, arr->capacity/2);
    }

    int last_idx = arr->len-1;
    int last = *arr->ptr+last_idx;

    *(arr->ptr+last_idx) = 0;
    arr->len -= 1;

    return last;
}


void insert(struct Array* arr, int indx, int item) {
    if (arr->len == arr->capacity) {
        resize(arr, arr->capacity * 2);
    }
      
    for (int i = arr->len - 1; i >= indx; i--) {
        set(arr, i+1, at(arr, i));
        set(arr, i, 0);
    }

    set(arr, indx, item);
    arr->len++;
}

void prepend(struct Array* arr, int item) {
    insert(arr, 0, item); 
}

void delete(struct Array* arr, int indx) {
    if (arr->len == (arr->capacity)/4) {
        resize(arr, arr->capacity/2);
    }

    set(arr, indx, 0);
    for (int i = indx+1; i < arr->len; i++) {
        set(arr, i-1, at(arr, i));
        set(arr, i, 0);
    }
    arr->len--;
}

void remove_itm(struct Array* arr, int item) {
    for (int i = 0; i < arr->len; i++)  {
        if (*(arr->ptr+i) == item) {
            delete(arr, i);
        }
    }
}

int main() {
    int *p, l, bsize;
    time_t t;

    bsize = 16, l = 0;
    p = (int*) malloc(sizeof(int) * bsize);

    struct Array arr = {p, l, bsize};

    for (int i = 0; i < 10; i++) {
        push(&arr, i);
    }

    print_array(&arr);
}
