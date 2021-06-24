#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* front(struct Node* head) {
    return head;
}

struct Node* back(struct Node* head) {
    while (head->next != NULL) {
        head = head->next;
    }
    return head;
}

bool empty(struct Node* head) {
    return head == NULL;
}

int size(struct Node* head) {
    int s = 0;
    while (head != NULL) {
        head = head->next;
        s++;
    }
    return s;
}

struct Node* value_at(struct Node* head, int indx) {
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

void print_ll(struct Node* head) {
    while (head != NULL) {
        printf("%d\n", head->data);
        head = head->next;
    }
}

void *push_front(struct Node** head_ptr, int key) {
    struct Node *new_elm = malloc(sizeof (struct Node));
    new_elm->data = key;
    new_elm->next = NULL;

    if (*head_ptr == NULL){
        *head_ptr = new_elm;
    }
    else {
        new_elm->next = *head_ptr;
        *head_ptr = new_elm;
    }
    return head_ptr;
}

int main() {
    struct Node *head = NULL;

    push_front(&head, 5);
    push_front(&head, 4);
    push_front(&head, 3);
    push_front(&head, 2);
    push_front(&head, 1);

    printf("%d", empty(head));
}
