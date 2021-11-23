#include <stdbool.h>

struct BstNode {
    int key;
    struct BstNode *left;
    struct BstNode *right;
};

struct BstNode *bst_get_min(struct BstNode *root);
struct BstNode *bst_get_max(struct BstNode *root);
int bst_get_height(struct BstNode *root);
bool valid_bst(struct BstNode *root, int min, int max);
bool bst_exists(struct BstNode *root, int key);
void bst_print(struct BstNode *root);
int bst_len(struct BstNode *root);
void bst_insert(struct BstNode **root, int key);
void bst_delete_all(struct BstNode *root, struct BstNode *key);
struct BstNode *bst_delete(struct BstNode *root, struct BstNode *node, int key);
struct BstNode *bst_get_successor(struct BstNode *root, struct BstNode *node);
