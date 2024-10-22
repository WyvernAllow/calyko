#ifndef CK_LEXER_H
#define CK_LEXER_H
#include <stdint.h>
#include <stddef.h>

#include "token_type.h"

typedef struct ck_lexer {
    const char *source;
    size_t start;
    size_t current;

    size_t line;
} ck_lexer;

typedef struct ck_token {
    ck_token_type type;
    size_t start;
    size_t length;

    size_t line;
} ck_token;

void ck_lexer_init(ck_lexer *lexer, const char *source);
ck_token ck_lexer_next(ck_lexer *lexer);

#endif /* CK_LEXER_H */
