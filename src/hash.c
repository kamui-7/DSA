#include "hash.h"
#include <stdlib.h>

int hash(int k, int m) { return k % m; }

int avail_index(struct HashTable *ht, int key) {
    int index = hash(key, ht->capacity);
    if (ht->num_items == ht->capacity) {
        return -1;
    }
    while (ht->data[index] != NULL) {
        if (index == ht->capacity - 1) {
            index = 0;
        } else {
            index++;
        }
    }
    return index;
}

int find_index(struct HashTable *ht, int key) {
    int idx = hash(key, ht->capacity);
    int start_idx = idx;
    bool passed_circular = false;
    while (ht->data[idx] != NULL && ht->data[idx]->key != key) {
        if (idx == ht->capacity - 1) {
            if (passed_circular && idx == start_idx) {
                break;
            }
            idx = 0;
            passed_circular = true;
        } else {
            idx++;
        }
    }
    return idx;
}

void add(struct HashTable *ht, int key, int value) {
    int idx = avail_index(ht, key);
    struct Entry *ent = malloc(sizeof(struct Entry));
    ent->key = key;
    ent->value = value;
    ht->data[idx] = ent;
    ht->num_items++;
}

int get(struct HashTable *ht, int key) {
    int idx = find_index(ht, key);
    return ht->data[idx]->value;
}

bool exists(struct HashTable *ht, int key) {
    int idx = find_index(ht, key);
    return ht->data[idx] != NULL;
}

void remove(struct HashTable *ht, int key);
