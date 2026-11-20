#ifndef SIZE_CHECK_H
#define SIZE_CHECK_H

#include <stddef.h>

enum size_result { SIZE_OK, SIZE_EMPTY, SIZE_OVERFLOW, SIZE_OVER_BUDGET };

enum size_result checked_bytes(size_t count, size_t item_size,
                               size_t budget, size_t *bytes);
const char *size_result_name(enum size_result result);

#endif
