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

void it_deletes(void **state) {
    struct MaxHeap heap = ((struct teststate_t *)(*state))->heap;
    test_data(&heap);
    assert_int_equal(heap_get_max(&heap), 8);
    heap_remove(&heap, 0);
    assert_int_equal(heap_get_max(&heap), 4);
    heap_remove(&heap, 0);
    assert_int_equal(heap_get_max(&heap), 3);
}

void it_gets_size(void **state) {
    struct MaxHeap heap = ((struct teststate_t *)(*state))->heap;
    test_data(&heap);
    assert_int_equal(heap_len(&heap), 4);
}

void it_is_empty(void **state) {
    struct MaxHeap heap = ((struct teststate_t *)(*state))->heap;
    assert_int_equal(heap_is_empty(&heap), true);
}

void it_extracts_max(void **state) {
    struct MaxHeap heap = ((struct teststate_t *)(*state))->heap;
    test_data(&heap);
    int max = heap_extract_max(&heap);
    assert_int_equal(max, 8);
    assert_int_not_equal(heap_get_max(&heap), 8);
}

/* void it_heapifies_array(void **state) {
    struct MaxHeap heap = ((struct teststate_t *)(*state))->heap;
    test_data(&heap);
    int max = extract_max(&heap);
    assert_int_equal(max, 8);
    assert_int_not_equal(heap_get_max(&heap), 8);
} */

void it_performs_heapsort(void **state) {
    int arr[] = {23, 3, 42, 18, 7, 21};
    heap_sort(arr, 6);
    assert_int_equal(arr[0], 3);
    assert_int_equal(arr[5], 42);
}

int main(void) {
    printf("Starting heap tests...\n");
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(it_inserts, test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(it_deletes, test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_size, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_is_empty, test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(it_extracts_max, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_performs_heapsort, test_setup,
                                        test_teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
