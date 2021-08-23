#include <stdbool.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
};

struct Node *
get_min(struct Node *root); // returns the minimum value stored in the tree
struct Node *
get_max(struct Node *root); // returns the maximum value stored in the tree
int get_height(struct Node *root); // returns the height in nodes (single node's
                                   // height is 1)
bool is_binary_search_tree(struct Node *root, int min, int max);
bool is_in_tree(struct Node *root,
                int key); // returns true if given value exists in the tree
void print_values(
    struct Node *root); // prints the values in the tree, from min to max
int get_node_count(struct Node *root);         // get count of values stored
void insert_leaf(struct Node **root, int key); // insert value into tree
void delete_tree();
void delete_value();
struct Node *get_successor(struct Node *root, int key); // returns next-highest value in tree after given
                              // value, -1 if none
