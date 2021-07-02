#include "queue.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void enqueue_lq(struct ListQueue *lq, int value) {
    struct Node *new_node = malloc(sizeof(struct Node));
    new_node->data = value;

    if (!lq->head) {
        lq->head = new_node;
        lq->tail = new_node;
    } else {
        lq->tail->next = new_node;
        lq->tail = new_node;
    }
}

struct Node *dequeue_lq(struct ListQueue *lq) {
    struct Node *head = lq->head;
    struct Node *temp = head->next;
    head->next = NULL;
    lq->head = temp;
    return head;
}

bool empty_lq(struct ListQueue *lq) { return lq->head == NULL; }

void enqueue_cb(struct ArrayQueue *aq, int value) {
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

int dequeue_cb(struct ArrayQueue *aq) {
    int popped = *aq->tail;
    aq->tail = aq->tail + sizeof(int);
    if (aq->tail == aq->buffer_end) {
        aq->tail = aq->buffer;
    }
    aq->count--;
    return popped;
}

bool empty_cb(struct ArrayQueue *aq) { return aq->count == 0; }
bool full_cb(struct ArrayQueue *aq) { return aq->count == aq->capacity; }
