#include "utils.h"
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

struct Node *get_min(struct Node *root) {
    while (root->left) {
        root = root->left;
    }
    return root;
}

struct Node *get_max(struct Node *root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}

void insert_leaf(struct Node **root, int key) {
    if (*root == NULL) {
        struct Node *new_node = malloc(sizeof(struct Node));
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->key = key;
        *root = new_node;
    } else if (key <= (*root)->key) {
        insert_leaf(&(*root)->left, key);
    } else {
        insert_leaf(&(*root)->right, key);
    }
}

int get_height(struct Node *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + MAX(get_height(root->left), get_height(root->right));
}

int get_node_count(struct Node *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + get_node_count(root->left) + get_node_count(root->right);
}

bool is_binary_search_tree(struct Node *root, int min, int max) {
    if (root == NULL) {
        return true;
    }

    if (root->key < min || root->key > max) {
        return false;
    }

    return is_binary_search_tree(root->left, min, root->key) &&
           is_binary_search_tree(root->right, root->key, max);
}

bool is_in_tree(struct Node *root, int key) {
    if (root == NULL) {
        return false;
    }

    if (root->key == key) {
        return true;
    }

    if (key > root->key) {
        return is_in_tree(root->right, key);
    } else {
        return is_in_tree(root->left, key);
    }
}

void print_values(struct Node *root) {
    if (root == NULL) {
        return;
    }

    print_values(root->left);
    printf("%d\n", root->key);
    print_values(root->right);
}

void delete_tree() {}

void delete_value() {}

struct Node *get_successor(struct Node *root, int key) {}
