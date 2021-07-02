#include <sys/types.h>
#include <stdbool.h>
#include "linked_list.h"

struct ListQueue {
    struct Node *head;
    struct Node *tail;
};

struct ArrayQueue {
    int *head;
    int *tail;
    size_t capacity;
    size_t count;
    int *buffer;
    int *buffer_end;
};

void enqueue_lq(struct ListQueue *lq, int value);
struct Node *dequeue_lq(struct ListQueue *lq);
bool empty_lq(struct ListQueue *lq);

void enqueue_cb(struct ArrayQueue *aq, int value);
int dequeue_cb(struct ArrayQueue *aq);
bool empty_cb(struct ArrayQueue *aq);
bool full_cb(struct ArrayQueue *aq);
