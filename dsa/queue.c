#include "queue.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void lq_enqueue(struct ListQueue *lq, int value) {
    struct ListNode *new_node = malloc(sizeof(struct ListNode));
    new_node->data = value;

    if (!lq->head) {
        lq->head = new_node;
        lq->tail = new_node;
    } else {
        lq->tail->next = new_node;
        lq->tail = new_node;
    }
}

struct ListNode *lq_dequeue(struct ListQueue *lq) {
    struct ListNode *head = lq->head;
    struct ListNode *temp = head->next;
    head->next = NULL;
    lq->head = temp;
    return head;
}

bool lq_empty(struct ListQueue *lq) { return lq->head == NULL; }

void cb_enqueue(struct ArrayQueue *aq, int value) {
    if (aq->count == aq->capacity) {
        return;
    }
    *(aq->head) = value;
    aq->head = aq->head + sizeof(int);
    if (aq->head == aq->buffer_end) {
        aq->head = aq->buffer;
    }
    aq->count++;
}

int cb_dequeue(struct ArrayQueue *aq) {
    int popped = *aq->tail;
    aq->tail = aq->tail + sizeof(int);
    if (aq->tail == aq->buffer_end) {
        aq->tail = aq->buffer;
    }
    aq->count--;
    return popped;
}

bool cb_empty(struct ArrayQueue *aq) { return aq->count == 0; }
bool cb_full(struct ArrayQueue *aq) { return aq->count == aq->capacity; }
