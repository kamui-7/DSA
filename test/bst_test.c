#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>
#include <malloc.h>
#include "bst.h"

struct teststate_t {
    struct Node *tree;
};

static int test_setup(void **state) {
    struct teststate_t *teststate = malloc(sizeof(struct teststate_t));
    teststate->tree = NULL;
    *state = teststate;
    return 0;
}

static int test_teardown(void **state) {
    free(*state);
    return 0;
}

void test_data(struct Node **root) {
    insert_leaf(root, 10);
    insert_leaf(root, 7);
    insert_leaf(root, 13);
    insert_leaf(root, 8);
    insert_leaf(root, 2);
    insert_leaf(root, 4);
}

void it_inserts(void **state) {
    struct Node *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    assert_int_equal(root->key, 10);
    assert_int_equal(root->left->key, 7);
    assert_int_equal(root->left->right->key, 8);
    assert_int_equal(root->right->key, 13);
}

void it_gets_minimum(void **state) {
    struct Node *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    struct Node *min = get_min(root);
    assert_int_equal(min->key, 2);
}

void it_gets_maximum(void **state) {
    struct Node *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    struct Node *max = get_max(root);
    assert_int_equal(max->key, 13);
}

void it_gets_height(void **state) {
    struct Node *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    int height = get_height(root);
    assert_int_equal(height, 4);
}

void it_gets_node_count(void **state) {
    struct Node *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    int count = get_node_count(root);
    assert_int_equal(count, 6);
}

void it_is_a_bst(void **state) {
    struct Node *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    bool is_bst = is_binary_search_tree(root, INT16_MIN, INT16_MAX);
    assert_int_equal(is_bst, true);

    struct Node *wrong_node = malloc(sizeof(struct Node));
    wrong_node->left = NULL;
    wrong_node->right = NULL;
    wrong_node->key = 2;

    root->right->left = wrong_node;
    is_bst = is_binary_search_tree(root, INT16_MIN, INT16_MAX);
    assert_int_equal(is_bst, false);
}

void it_is_in_tree(void **state) {
    struct Node *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    int in_tree = is_in_tree(root, 2);
    assert_int_equal(in_tree, true);

    in_tree = is_in_tree(root, 73);
    assert_int_equal(in_tree, false);
}

int main(void) {
    printf("Starting binary search tree tests...\n");
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(it_inserts, test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_minimum, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_maximum, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_height, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_node_count, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_is_a_bst, test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(it_is_in_tree, test_setup,
                                        test_teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
