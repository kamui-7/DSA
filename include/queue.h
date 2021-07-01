#include <stdbool.h>
#include "linked_list.h"

struct ListQueue {
    struct Node *head;
    struct Node *tail;
};

void enqueue_lq(struct ListQueue *lq, int value);
struct Node *dequeue_lq(struct ListQueue *lq);
bool empty_lq(struct ListQueue *lq);
void print_lq(struct ListQueue *lq);
