#include "utils.h"
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

struct BstNode *bst_get_min(struct BstNode *root) {
    while (root->left) {
        root = root->left;
    }
    return root;
}

struct BstNode *bst_get_max(struct BstNode *root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}

void bst_insert(struct BstNode **root, int key) {
    if (*root == NULL) {
        struct BstNode *new_node = malloc(sizeof(struct BstNode));
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->key = key;
        *root = new_node;
    } else if (key <= (*root)->key) {
        bst_insert(&(*root)->left, key);
    } else {
        bst_insert(&(*root)->right, key);
    }
}

int bst_get_height(struct BstNode *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + MAX(bst_get_height(root->left), bst_get_height(root->right));
}

int bst_len(struct BstNode *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + bst_len(root->left) + bst_len(root->right);
}

bool valid_bst(struct BstNode *root, int min, int max) {
    if (root == NULL) {
        return true;
    }

    if (root->key < min || root->key > max) {
        return false;
    }

    return valid_bst(root->left, min, root->key) &&
           valid_bst(root->right, root->key, max);
}

bool bst_exists(struct BstNode *root, int key) {
    if (root == NULL) {
        return false;
    }

    if (root->key == key) {
        return true;
    }

    if (key > root->key) {
        return bst_exists(root->right, key);
    } else {
        return bst_exists(root->left, key);
    }

    return false;
}

void print_values(struct BstNode *root) {
    if (root == NULL) {
        return;
    }

    print_values(root->left);
    printf("%d\n", root->key);
    print_values(root->right);
}

void bst_delete_all(struct BstNode *root, struct BstNode *key) {
    if (key->left) {
        bst_delete_all(root, key->left);
    } else if (key->right) {
        bst_delete_all(root, key->right);
    }
    bst_delete(root, root, key->key);
}

struct BstNode *bst_next_greater(struct BstNode *root, struct BstNode *node) {
    struct BstNode *succ;
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

struct BstNode *bst_get_successor(struct BstNode *root, struct BstNode *node) {
    if (node->right != NULL) {
        return bst_get_min(node->right);
    } else {
        return bst_next_greater(root, node);
    }
}

struct BstNode *bst_delete(struct BstNode *root, struct BstNode *node,
                           int key) {
    if (node == NULL)
        return NULL;

    if (key < node->key) {
        node->left = bst_delete(root, node->left, key);
    } else if (key > node->key) {
        node->right = bst_delete(root, node->right, key);
    } else {
        if (node->left == NULL && node->right == NULL) {
            free(node);
            node = NULL;
        } else if (node->left == NULL) {
            struct BstNode *temp = node;
            node = node->right;
            free(temp);
        } else if (node->right == NULL) {
            struct BstNode *temp = node;
            node = node->left;
            free(temp);
        } else {
            struct BstNode *succ = bst_get_successor(root, node);
            node->key = succ->key;
            free(succ);
        }
    }
    return node;
}
