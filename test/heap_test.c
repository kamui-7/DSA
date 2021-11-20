#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>
#include <malloc.h>
#include "heap.h"

struct teststate_t {
    struct MaxHeap heap;
};

static int test_setup(void **state) {
    struct teststate_t *teststate = malloc(sizeof(struct teststate_t));
    struct MaxHeap heap = {0, CAPACITY, {}};
    teststate->heap = heap;
    *state = teststate;
    return 0;
}

static int test_teardown(void **state) {
    free(*state);
    return 0;
}

void test_data(struct MaxHeap *heap) {
    heap_insert(heap, 1);
    heap_insert(heap, 3);
    heap_insert(heap, 4);
    heap_insert(heap, 8);
}

void it_inserts(void **state) {
    struct MaxHeap heap = ((struct teststate_t *)(*state))->heap;
    test_data(&heap);
    assert_int_equal(heap_get_max(&heap), 8);
}

int main(void) {
    printf("Starting heap tests...\n");
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(it_inserts, test_setup, test_teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
