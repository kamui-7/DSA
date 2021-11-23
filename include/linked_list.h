#include <stdbool.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *list_front(struct ListNode *head);
struct ListNode *list_back(struct ListNode *head);
bool list_empty(struct ListNode *head);
int list_len(struct ListNode *head);
struct ListNode *list_at(struct ListNode *head, int indx);
void list_print(struct ListNode *head);
void list_push_front(struct ListNode **head_ptr, int key);
struct ListNode *list_pop_front(struct ListNode **head_ptr);
void list_push_back(struct ListNode **head_ptr, int key);
struct ListNode *list_pop_back(struct ListNode **head_ptr);
void list_insert(struct ListNode **head_ptr, int index, int key);
void list_erase(struct ListNode **head_ptr, int index);
struct ListNode *list_n_from_end(struct ListNode *head_ptr, int n);
void list_remove(struct ListNode **head_ptr, int value);
void list_reverse(struct ListNode **head_ptr);
