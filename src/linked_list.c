#include "linked_list.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode *list_front(struct ListNode *head) {
    return head;
}

struct ListNode *list_back(struct ListNode *head) {
    while (head->next != NULL) {
        head = head->next;
        
    }
    return head;
}

bool list_empty(struct ListNode *head) { return head == NULL; }

int list_len(struct ListNode *head) {
    int s = 0;
    while (head != NULL) {
        head = head->next;
        s++;
    }
    return s;
}

struct ListNode *list_at(struct ListNode *head, int indx) {
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

void list_print(struct ListNode *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

struct ListNode *list_create_elm(int key) {
    struct ListNode *new_elm = malloc(sizeof(struct ListNode));
    new_elm->data = key;
    new_elm->next = NULL;
    return new_elm;
}

void list_push_front(struct ListNode **head_ptr, int key) {
    struct ListNode *new_elm = list_create_elm(key);

    if (*head_ptr == NULL) {
        *head_ptr = new_elm;
    } else {
        new_elm->next = *head_ptr;
        *head_ptr = new_elm;
    }
}

struct ListNode *list_pop_front(struct ListNode **head_ptr) {
    struct ListNode *front = *head_ptr;
    *head_ptr = (*head_ptr)->next;
    return front;
}

void list_push_back(struct ListNode **head_ptr, int key) {
    struct ListNode *new_elm = list_create_elm(key);
    if (!*head_ptr) {
        *head_ptr = new_elm;
    } else {
        struct ListNode *back_elm = list_back(*head_ptr);
        back_elm->next = new_elm;
    }
}

struct ListNode *list_pop_back(struct ListNode **head_ptr) {
    struct ListNode *second_to_last = *head_ptr;
    if (!second_to_last) {
        return NULL;
    }

    while (second_to_last->next->next != NULL) {
        second_to_last = second_to_last->next;
    }
    struct ListNode *last = second_to_last->next;
    second_to_last->next = NULL;
    return last;
}

void list_insert(struct ListNode **head_ptr, int index, int key) {
    struct ListNode *head = *head_ptr;
    int s = 0;
    while (head != NULL && s < index - 1) {
        head = head->next;
        s++;
    }
    if (!head) {
        return;
    }
    struct ListNode *new_elm = list_create_elm(key);
    struct ListNode *after_indx = head->next;
    head->next = new_elm;
    new_elm->next = after_indx;
}

void list_erase(struct ListNode **head_ptr, int index) {
    struct ListNode *head = *head_ptr;
    int s = 0;
    while (head != NULL && s < index - 1) {
        head = head->next;
        s++;
    }
    if (!head) {
        return;
    }
    struct ListNode *after_indx = head->next;
    head->next = after_indx->next;
    free(after_indx);
}

struct ListNode *list_n_from_end(struct ListNode *head_ptr, int n) {
    int indx = (list_len(head_ptr) - 1) - n;
    return list_at(head_ptr, indx);
}

void list_remove(struct ListNode **head_ptr, int value) {
    struct ListNode *head = *head_ptr;
    struct ListNode *prev = NULL;
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

void list_reverse(struct ListNode **head_ptr) {
    struct ListNode *head = *head_ptr;
    struct ListNode *next = head->next;
    struct ListNode *prev = NULL;

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
