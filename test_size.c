#include "size_check.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

static void check(size_t count, size_t size, size_t budget,
                   enum size_result expected, size_t expected_bytes) {
    size_t bytes = 123;
    assert(checked_bytes(count, size, budget, &bytes) == expected);
    assert(bytes == expected_bytes);
}

int main(void) {
    check(8, 16, 1024, SIZE_OK, 128);
    check(64, 16, 1024, SIZE_OK, 1024);
    check(65, 16, 1024, SIZE_OVER_BUDGET, 0);
    check(0, 16, 1024, SIZE_EMPTY, 0);
    check(1, 0, 1024, SIZE_EMPTY, 0);
    check(1, 1, 0, SIZE_OVER_BUDGET, 0);
    check(SIZE_MAX, 1, SIZE_MAX, SIZE_OK, SIZE_MAX);
    check(SIZE_MAX, 2, SIZE_MAX, SIZE_OVERFLOW, 0);
    check(SIZE_MAX / 16, 16, SIZE_MAX, SIZE_OK, (SIZE_MAX / 16) * 16);
    check(SIZE_MAX / 16 + 1, 16, SIZE_MAX, SIZE_OVERFLOW, 0);
    check(1, SIZE_MAX, SIZE_MAX, SIZE_OK, SIZE_MAX);
    check(2, SIZE_MAX, SIZE_MAX, SIZE_OVERFLOW, 0);
    puts("12 boundary checks passed");
    return 0;
}
