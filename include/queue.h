#include <sys/types.h>
#include <stdbool.h>
#include "linked_list.h"

struct ListQueue {
    struct ListNode *head;
    struct ListNode *tail;
};

struct ArrayQueue {
    int *head;
    int *tail;
    size_t capacity;
    size_t count;
    int *buffer;
    int *buffer_end;
};

void lq_enqueue(struct ListQueue *lq, int value);
struct ListNode *lq_dequeue(struct ListQueue *lq);
bool lq_empty(struct ListQueue *lq);

void cb_enqueue(struct ArrayQueue *aq, int value);
int cb_dequeue(struct ArrayQueue *aq);
bool cb_empty(struct ArrayQueue *aq);
bool cb_full(struct ArrayQueue *aq);
