#include "chunk.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void ck_chunk_init(ck_chunk *chunk) {
    chunk->code = NULL;
    chunk->code_len = 0;
    chunk->code_cap = 0;
    chunk->constants_len = 0;
}

void ck_chunk_free(ck_chunk *chunk) {
    free(chunk->code);
}

void ck_chunk_write(ck_chunk *chunk, uint8_t byte) {
    if (chunk->code_len + 1 > chunk->code_cap) {
        chunk->code_cap = CK_MAX(8, chunk->code_cap * 2);
        chunk->code =
            realloc(chunk->code, chunk->code_cap * sizeof(*chunk->code));
        if (!chunk->code) {
            fprintf(stderr, "Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
    }

    chunk->code[chunk->code_len] = byte;
    chunk->code_len++;
}

uint8_t ck_chunk_write_constant(ck_chunk *chunk, ck_value value) {
    if (chunk->constants_len >= CK_MAX_CONSTANTS) {
        fprintf(stderr, "Too many constants in chunk");
        exit(EXIT_FAILURE);
    }

    chunk->constants[chunk->constants_len] = value;
    chunk->constants_len++;
    return (uint8_t)(chunk->constants_len - 1);
}
