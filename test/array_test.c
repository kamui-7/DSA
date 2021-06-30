#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>
#include <malloc.h>
#include <stdio.h>
#include "array.h"

struct teststate_t {
    struct Array vec;
};

static int test_setup(void **state) {
    struct teststate_t *teststate = malloc(sizeof(struct teststate_t));
    int *p, l, bsize;
    bsize = 16, l = 0;
    p = malloc(sizeof(int) * bsize);
    struct Array arr = {p, l, bsize};
    teststate->vec = arr;
    *state = teststate;
    return 0;
}

static int test_teardown(void **state) {
    free(*state);
    return 0;
}

void it_pushes_item(void **state) {
    struct Array arr = ((struct teststate_t *)(*state))->vec;
    push(&arr, 1);
    int last_elm = at(&arr, arr.len - 1);
    assert_int_equal(last_elm, 1);
}

void it_finds_item(void **state) {
    struct Array arr = ((struct teststate_t *)(*state))->vec;
    for (int i = 0; i < 10; i++)
        push(&arr, i);
    int indx = find(&arr, 3);
    assert_int_equal(indx, 3);
}

void it_is_empty(void **state) {
    struct Array arr = ((struct teststate_t *)(*state))->vec;
    bool empty = is_empty(&arr);
    assert_int_equal(empty, true);
}

void it_accesses_first_item(void **state) {
    struct Array arr = ((struct teststate_t *)(*state))->vec;
    push(&arr, 5);
    int first_elm = at(&arr, 0);
    assert_int_equal(first_elm, 5);
}

void it_pops_item(void **state) {
    struct Array arr = ((struct teststate_t *)(*state))->vec;
    push(&arr, 1);
    int elm = pop(&arr);
    assert_int_equal(elm, 1);
}

void it_inserts_item(void **state) {
    struct Array arr = ((struct teststate_t *)(*state))->vec;
    for (int i = 0; i < 10; i++)
        push(&arr, i);
    insert(&arr, 3, 777);
    int elm = at(&arr, 3);
    assert_int_equal(elm, 777);
}

void it_prepends_item(void **state) {
    struct Array arr = ((struct teststate_t *)(*state))->vec;
    for (int i = 0; i < 10; i++)
        push(&arr, i);
    prepend(&arr, 777);
    int elm = at(&arr, 0);
    assert_int_equal(elm, 777);
}

void it_removes_by_index(void **state) {
    struct Array arr = ((struct teststate_t *)(*state))->vec;
    for (int i = 0; i < 10; i++)
        push(&arr, i);
    erase(&arr, 0);
    int elm = at(&arr, 0);
    assert_int_equal(elm, 1);
}

void it_removes_by_key(void **state) {
    struct Array arr = ((struct teststate_t *)(*state))->vec;
    for (int i = 0; i < 10; i++)
        push(&arr, i);
    remove_itm(&arr, 7);
    int elm = at(&arr, 7);
    assert_int_equal(elm, 8);
}

int main(void) {
    printf("Starting array tests...\n");
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(it_pushes_item, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_finds_item, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_is_empty, test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(it_accesses_first_item, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_pops_item, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_inserts_item, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_prepends_item, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_removes_by_index, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_removes_by_key, test_setup,
                                        test_teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
