#include "linked_list.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node *front(struct Node *head) {
    return head;
}

struct Node *back(struct Node *head) {
    while (head->next != NULL) {
        head = head->next;
    }
    return head;
}

bool empty(struct Node *head) { return head == NULL; }

int size(struct Node *head) {
    int s = 0;
    while (head != NULL) {
        head = head->next;
        s++;
    }
    return s;
}

struct Node *value_at(struct Node *head, int indx) {
    int s = 0;
    while (head != NULL) {
        if (s == indx) {
            return head;
        }
        head = head->next;
        s++;
    }
    return NULL;
}

void print_ll(struct Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

struct Node *create_elm(int key) {
    struct Node *new_elm = malloc(sizeof(struct Node));
    new_elm->data = key;
    new_elm->next = NULL;
    return new_elm;
}

void push_front(struct Node **head_ptr, int key) {
    struct Node *new_elm = create_elm(key);

    if (*head_ptr == NULL) {
        *head_ptr = new_elm;
    } else {
        new_elm->next = *head_ptr;
        *head_ptr = new_elm;
    }
}

struct Node *pop_front(struct Node **head_ptr) {
    struct Node *front = *head_ptr;
    *head_ptr = (*head_ptr)->next;
    return front;
}

void push_back(struct Node **head_ptr, int key) {
    struct Node *new_elm = create_elm(key);
    if (!*head_ptr) {
        *head_ptr = new_elm;
    } else {
        struct Node *back_elm = back(*head_ptr);
        back_elm->next = new_elm;
    }
}

struct Node *pop_back(struct Node **head_ptr) {
    struct Node *second_to_last = *head_ptr;
    if (!second_to_last) {
        return NULL;
    }

    while (second_to_last->next->next != NULL) {
        second_to_last = second_to_last->next;
    }
    struct Node *last = second_to_last->next;
    second_to_last->next = NULL;
    return last;
}

void insert_node(struct Node **head_ptr, int index, int key) {
    struct Node *head = *head_ptr;
    int s = 0;
    while (head != NULL && s < index - 1) {
        head = head->next;
        s++;
    }
    if (!head) {
        return;
    }
    struct Node *new_elm = create_elm(key);
    struct Node *after_indx = head->next;
    head->next = new_elm;
    new_elm->next = after_indx;
}

void erase_node(struct Node **head_ptr, int index) {
    struct Node *head = *head_ptr;
    int s = 0;
    while (head != NULL && s < index - 1) {
        head = head->next;
        s++;
    }
    if (!head) {
        return;
    }
    struct Node *after_indx = head->next;
    head->next = after_indx->next;
    free(after_indx);
}

struct Node *value_n_from_end(struct Node *head_ptr, int n) {
    int indx = (size(head_ptr) - 1) - n;
    return value_at(head_ptr, indx);
}

void remove_value(struct Node **head_ptr, int value) {
    struct Node *head = *head_ptr;
    struct Node *prev = NULL;
    while (head != NULL) {
        if (head->data == value) {
            if (!prev) {
                *head_ptr = head->next;
            } else {
                prev->next = head->next;
            }
            free(head);
            return;
        }
        prev = head;
        head = head->next;
    }
}

void reverse(struct Node **head_ptr) {
    struct Node *head = *head_ptr;
    struct Node *next = head->next;
    struct Node *prev = NULL;

    while (head != NULL) {
        if (!prev) {
            head->next = NULL;
        } else {
            head->next = prev;
        }

        prev = head;
        head = next;
        if (!head) {
            break;
        }
        next = head->next;
    }
    *head_ptr = prev;
}
