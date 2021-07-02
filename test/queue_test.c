#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>
#include <malloc.h>
#include <stdio.h>
#include "queue.h"

struct teststate_t {
    struct ListQueue lq;
    struct ArrayQueue aq;
};

static int test_setup(void **state) {
    struct teststate_t *teststate = malloc(sizeof(struct teststate_t));
    int num_items = 5;
    teststate->aq.buffer = malloc(num_items * sizeof(int));
    teststate->aq.buffer_end = teststate->aq.buffer + num_items * sizeof(int);
    teststate->aq.capacity = num_items;
    teststate->aq.count = 0;
    teststate->aq.head = teststate->aq.buffer;
    teststate->aq.tail = teststate->aq.buffer;

    teststate->lq.head = NULL;
    teststate->lq.tail = NULL;
    *state = teststate;
    return 0;
}

static int test_teardown(void **state) {
    free(((struct teststate_t *)(*state))->aq.buffer);
    free(*state);
    return 0;
}

void it_is_empty_ll(void **state) {
    struct ListQueue lq = ((struct teststate_t *)(*state))->lq;
    bool em = empty_lq(&lq);
    assert_int_equal(em, true);
}

void it_enqueues_and_dequeues_node_ll(void **state) {
    struct ListQueue lq = ((struct teststate_t *)(*state))->lq;
    for (int i = 5; i > 0; i--)
        enqueue_lq(&lq, i);
    int first = dequeue_lq(&lq)->data;
    int second = dequeue_lq(&lq)->data;
    assert_int_equal(first, 5);
    assert_int_equal(second, 4);
}

void it_is_empty_aq(void **state) {
    struct ArrayQueue aq = ((struct teststate_t *)(*state))->aq;
    bool em = empty_cb(&aq);
    assert_int_equal(em, true);
}

void it_is_full(void **state) {
    struct ArrayQueue aq = ((struct teststate_t *)(*state))->aq;
    for (int i = 5; i > 0; i--)
        enqueue_cb(&aq, i);
    bool fl = full_cb(&aq);
    assert_int_equal(fl, true);
}

void it_enqueues_and_dequeues_node_cb(void **state) {
    struct ArrayQueue aq = ((struct teststate_t *)(*state))->aq;
    for (int i = 5; i > 0; i--)
        enqueue_cb(&aq, i);
    int first = dequeue_cb(&aq);
    int second = dequeue_cb(&aq);
    assert_int_equal(first, 5);
    assert_int_equal(second, 4);
}

int main(void) {
    printf("Starting queue tests...\n");
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(it_is_empty_ll, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_is_full, test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(it_enqueues_and_dequeues_node_ll,
                                        test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(it_is_empty_aq, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_enqueues_and_dequeues_node_cb,
                                        test_setup, test_teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
