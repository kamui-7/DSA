#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>
#include <malloc.h>
#include "linked_list.h"

struct teststate_t {
    struct Node *head;
};

static int test_setup(void **state) {
    struct teststate_t *teststate = malloc(sizeof(struct teststate_t));
    teststate->head = NULL;
    *state = teststate;
    return 0;
}

static int test_teardown(void **state) {
    free(*state);
    return 0;
}

void it_gets_front(void **state) {
    struct Node *head = ((struct teststate_t *)(*state))->head;
    push_back(&head, 5);
    int f = front(head)->data;
    assert_int_equal(f, 5);
}

void it_gets_back(void **state) {
    struct Node *head = ((struct teststate_t *)(*state))->head;
    push_back(&head, 5);
    int b = back(head)->data;
    assert_int_equal(b, 5);
}

void it_is_empty(void **state) {
    struct Node *head = ((struct teststate_t *)(*state))->head;
    bool e = empty(head);
    assert_int_equal(e, true);
}

void it_calcs_size(void **state) {
    struct Node *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        push_back(&head, 0);
    int s = size(head);
    assert_int_equal(s, 5);
}

void it_gets_third_elm(void **state) {
    struct Node *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        push_back(&head, i);
    int third = value_at(head, 3)->data;
    assert_int_equal(third, 3);
}

void it_pushes_front(void **state) {
    struct Node *head = ((struct teststate_t *)(*state))->head;
    push_back(&head, 3);
    int first = value_at(head, 0)->data;
    assert_int_equal(first, 3);
}

void it_pops_front(void **state) {
    struct Node *head = ((struct teststate_t *)(*state))->head;
    push_back(&head, 3);
    int first = pop_front(&head)->data;
    assert_int_equal(first, 3);
}

void it_pushes_back(void **state) {
    struct Node *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        push_back(&head, i);
    int last = value_at(head, size(head) - 1)->data;
    assert_int_equal(last, 4);
}

void it_pops_back(void **state) {
    struct Node *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        push_back(&head, i);
    int last = pop_back(&head)->data;
    assert_int_equal(last, 4);
}

void it_inserts_node(void **state) {
    struct Node *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        push_back(&head, i);
    insert_node(&head, 2, 55);
    int val = value_at(head, 2)->data;
    assert_int_equal(val, 55);
}

void it_erases_node(void **state) {
    struct Node *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        push_back(&head, i);
    erase_node(&head, 2);
    int val = value_at(head, 2)->data;
    assert_int_equal(val, 3);
}

void it_gets_n_value_from_the_end(void **state) {
    struct Node *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        push_back(&head, i);
    int val = value_n_from_end(head, 2)->data;
    assert_int_equal(val, 2);
}

void it_removes_by_value(void **state) {
    struct Node *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        push_back(&head, i);
    remove_value(&head, 4);
    int val = back(head)->data;
    assert_int_not_equal(val, 4);
}

void it_reverses_list(void **state) {
    struct Node *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        push_back(&head, i);
    reverse(&head);
    int last = back(head)->data;
    assert_int_equal(last, 0);
}

int main(void) {
    printf("Starting linked list tests...\n");
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(it_gets_front, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_back, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_is_empty, test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(it_calcs_size, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_third_elm, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_pushes_front, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_pops_front, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_pushes_back, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_pops_back, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_inserts_node, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_erases_node, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_n_value_from_the_end,
                                        test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(it_removes_by_value, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_reverses_list, test_setup,
                                        test_teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
