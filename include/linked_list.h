#include <stdbool.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *front(struct Node *head);
struct Node *back(struct Node *head);
bool empty(struct Node *head);
int size(struct Node *head);
struct Node *value_at(struct Node *head, int indx);
void print_ll(struct Node *head);
struct Node *create_elm(int key);
void push_front(struct Node **head_ptr, int key);
struct Node *pop_front(struct Node **head_ptr);
void push_back(struct Node **head_ptr, int key);
struct Node *pop_back(struct Node **head_ptr);
void insert(struct Node **head_ptr, int index, int key);
void erase(struct Node **head_ptr, int index);
struct Node *value_n_from_end(struct Node *head_ptr, int n);
void remove_value(struct Node **head_ptr, int value);
void reverse(struct Node **head_ptr);
