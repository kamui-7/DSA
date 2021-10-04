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

    return false;
}

void print_values(struct Node *root) {
    if (root == NULL) {
        return;
    }

    print_values(root->left);
    printf("%d\n", root->key);
    print_values(root->right);
}

void delete_tree(struct Node *root, struct Node *key) {
    if (key->left) {
        delete_tree(root, key->left);
    } else if (key->right) {
        delete_tree(root, key->right);
    }
    delete_value(root, root, key->key);
}

struct Node *next_greater(struct Node *root, struct Node *node) {
    struct Node *succ;
    while (root != NULL) {
        if (root->key > node->key) {
            succ = root;
            root = root->left;
        } else if (root->key < node->key) {
            root = root->right;
        } else {
            return succ;
        }
    }
    return NULL;
}

struct Node *get_successor(struct Node *root, struct Node *node) {
    if (node->right != NULL) {
        return get_min(node->right);
    } else {
        return next_greater(root, node);
    }
}

struct Node *delete_value(struct Node *root, struct Node *node, int key) {
    if (node == NULL)
        return NULL;

    if (key < node->key) {
        node->left = delete_value(root, node->left, key);
    } else if (key > node->key) {
        node->right = delete_value(root, node->right, key);
    } else {
        if (node->left == NULL && node->right == NULL) {
            free(node);
            node = NULL;
        } else if (node->left == NULL) {
            struct Node *temp = node;
            node = node->right;
            free(temp);
        } else if (node->right == NULL) {
            struct Node *temp = node;
            node = node->left;
            free(temp);
        } else {
            struct Node *succ = get_successor(root, node);
            node->key = succ->key;
            free(succ);
        }
    }
    return node;
}
