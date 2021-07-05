#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdio.h>
#include <malloc.h>
#include "search.h"

struct teststate_t {
    int *array;
};

static int test_setup(void **state) {
    struct teststate_t *teststate = malloc(sizeof(struct teststate_t));
    teststate->array = malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        teststate->array[i] = i;
    }
    *state = teststate;
    return 0;
}

static int test_teardown(void **state) {
    free(*state);
    return 0;
}

void it_binary_searches(void **state) {
    int *arr = ((struct teststate_t *)(*state))->array;
    int indx = binary_search(arr, 7, 10);
    assert_int_equal(indx, 7);
}

void it_binary_searches_recursively(void **state) {
    int *arr = ((struct teststate_t *)(*state))->array;
    int indx = binary_search_recursive(arr, 7, 10);
    assert_int_equal(indx, 7);
}

int main(void) {
    printf("Starting search tests...\n");
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(it_binary_searches, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_binary_searches_recursively,
                                        test_setup, test_teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
