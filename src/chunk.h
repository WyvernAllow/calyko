#ifndef CK_CHUNK_H
#define CK_CHUNK_H
#include <stddef.h>
#include <stdint.h>

#include "value.h"

/* TODO: 256 constants is the amount addressable by a single byte.
 * This is quite limiting, and declaring this as a struct member
 * is also wasteful of memory. In the future this should be made larger,
 * and dynamically allocated.
 */
#define CK_MAX_CONSTANTS 256

typedef struct ck_chunk {
    uint8_t *code;
    size_t code_len;
    size_t code_cap;

    ck_value constants[CK_MAX_CONSTANTS];
    size_t constants_len;
} ck_chunk;

void ck_chunk_init(ck_chunk *chunk);
void ck_chunk_free(ck_chunk *chunk);
void ck_chunk_write(ck_chunk *chunk, uint8_t byte);
uint8_t ck_chunk_write_constant(ck_chunk *chunk, ck_value value);

#endif /* CK_CHUNK_H */
