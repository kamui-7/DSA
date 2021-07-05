#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>
#include <malloc.h>
#include <stdio.h>
#include "hash.h"

struct teststate_t {
    struct HashTable ht;
};

static int test_setup(void **state) {
    struct teststate_t *teststate = malloc(sizeof(struct teststate_t));
    teststate->ht.capacity = 100;
    teststate->ht.data = malloc(sizeof(struct Entry) * teststate->ht.capacity);
    teststate->ht.num_items = 0;
    *state = teststate;
    return 0;
}

static int test_teardown(void **state) {
    free(*state);
    return 0;
}

void it_adds_and_gets_pair(void **state) {
    struct HashTable ht = ((struct teststate_t *)(*state))->ht;
    add(&ht, 1732, 777);
    int itm = get(&ht, 1732);
    assert_int_equal(itm, 777);
}

void it_exists(void **state) {
    struct HashTable ht = ((struct teststate_t *)(*state))->ht;
    add(&ht, 1732, 777);
    bool e = exists(&ht, 1731);
    assert_int_equal(e, true);
}

int main(void) {
    printf("Starting hash tests...\n");
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(it_adds_and_gets_pair, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_exists, test_setup, test_teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
