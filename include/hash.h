#include <stdbool.h>

struct HtEntry {
    int key;
    int value;
    bool deleted;
};

struct HashTable {
    struct HtEntry **data;
    int capacity;
    int num_items;
};

int ht_hash(int k, int m);
void ht_add(struct HashTable *ht, int key, int value);
bool ht_exists(struct HashTable *ht, int key);
int ht_get(struct HashTable *ht, int key);
void ht_remove(struct HashTable *ht, int key);
