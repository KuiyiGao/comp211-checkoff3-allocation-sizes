#include "size_check.h"
#include <stdint.h>

enum size_result checked_bytes(size_t count, size_t item_size,
                               size_t budget, size_t *bytes) {
    *bytes = 0;
    if (count == 0 || item_size == 0) {
        return SIZE_EMPTY;
    }
    if (count > SIZE_MAX / item_size) {
        return SIZE_OVERFLOW;
    }
    size_t total = count * item_size;
    if (total > budget) {
        return SIZE_OVER_BUDGET;
    }
    *bytes = total;
    return SIZE_OK;
}

const char *size_result_name(enum size_result result) {
    switch (result) {
        case SIZE_OK: return "accepted";
        case SIZE_EMPTY: return "empty request";
        case SIZE_OVERFLOW: return "arithmetic overflow";
        case SIZE_OVER_BUDGET: return "over budget";
    }
    return "unknown";
}
