#include "size_check.h"
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Static_assert(UINT_MAX == UINT32_MAX, "This example needs 32-bit unsigned int");

static void show_case(const char *label, size_t count, size_t item_size,
                      size_t budget) {
    size_t bytes;
    enum size_result result = checked_bytes(count, item_size, budget, &bytes);
    printf("%-18s count=%zu size=%zu: %s", label, count, item_size,
           size_result_name(result));
    if (result == SIZE_OK) {
        printf(" (%zu bytes)", bytes);
    }
    putchar('\n');
}

int main(void) {
    unsigned int count = UINT_MAX / 16u + 2u;
    unsigned int item_size = 16u;
    unsigned int bytes = count * item_size;
    uint64_t actual = (uint64_t)count * item_size;

    printf("unsigned int: %zu bits; size_t: %zu bits\n",
           sizeof(unsigned int) * CHAR_BIT, sizeof(size_t) * CHAR_BIT);
    puts("\n1. A size calculation in 32-bit unsigned arithmetic");
    printf("count = %u, item size = %u\n", count, item_size);
    printf("mathematical product = %" PRIu64 "\n", actual);
    printf("stored byte count = %u\n", bytes);
    printf("checking stored bytes <= 1024: %s\n",
           bytes <= 1024u ? "accepted" : "rejected");

    puts("\n2. Check the original inputs before multiplying");
    show_case("normal", 8, 16, 1024);
    show_case("same large input", count, item_size, 1024);
    show_case("exact budget", 64, 16, 1024);
    show_case("over budget", 65, 16, 1024);
    show_case("empty", 0, 16, 1024);
    show_case("largest safe", SIZE_MAX / 16, 16, SIZE_MAX);
    show_case("next count", SIZE_MAX / 16 + 1, 16, SIZE_MAX);

    puts("\n3. Allocate only a small accepted request");
    size_t allocated;
    if (checked_bytes(8, 16, 1024, &allocated) != SIZE_OK) {
        return EXIT_FAILURE;
    }
    unsigned char *buffer = malloc(allocated);
    if (buffer == NULL) {
        fputs("allocation failed\n", stderr);
        return EXIT_FAILURE;
    }
    memset(buffer, 0, allocated);
    printf("allocated, initialized and freed %zu bytes\n", allocated);
    free(buffer);
    return EXIT_SUCCESS;
}
