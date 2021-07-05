#include <stdbool.h>

struct Entry {
    int key;
    int value;
    bool deleted;
};

struct HashTable {
    struct Entry **data;
    int capacity;
    int num_items;
};

int hash(int k, int m);
void add(struct HashTable *ht, int key, int value);
bool exists(struct HashTable *ht, int key);
int get(struct HashTable *ht, int key);
void remove_item(struct HashTable *ht, int key);
