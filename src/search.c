#include <stdio.h>

int binary_search(int *sorted_array, int key, int size) {
    int l, m, r;
    l = 0;
    r = size - 1;
    m = (r - l) / 2;

    while (1) {
        if (key == sorted_array[m]) {
            return m;
        } else if (key > sorted_array[m]) {
            l = m + 1;
        } else if (key < sorted_array[m]) {
            r = m - 1;
        }

        m = l + ((r - l) / 2);
    }

    return -1;
}

int bsearch(int *sorted_array, int key, int l, int m, int r) {
    int _tmp_l, _tmp_r, _tmp_m;
    _tmp_l = l;
    _tmp_r = r;
    _tmp_m = m;

    if (key == sorted_array[m]) {
        return m;
    } else if (key > sorted_array[m]) {
        _tmp_l = m + 1;
    } else if (key < sorted_array[m]) {
        _tmp_r = m - 1;
    }

    _tmp_m = l + ((r - l) / 2);
    return bsearch(sorted_array, key, _tmp_l, _tmp_m, _tmp_r);
}

int binary_search_recursive(int *sorted_array, int key, int size) {
    int l, m, r;
    l = 0;
    r = size - 1;
    m = (r - l) / 2;

    return bsearch(sorted_array, key, l, m, r);
}
