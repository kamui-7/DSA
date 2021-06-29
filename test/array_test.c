#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>
#include <malloc.h>
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
    struct teststate_t *tesstate = *state;
    print_array(&tesstate->vec);
    assert_non_null(*state);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(it_pushes_item, test_setup,
                                        test_teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
