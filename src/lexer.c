#include "lexer.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"

static bool is_at_end(const ck_lexer *lexer) {
    return lexer->source[lexer->current] == '\0';
}

static char peek(const ck_lexer *lexer) {
    return lexer->source[lexer->current];
}

static char peek_next(const ck_lexer *lexer) {
    if (is_at_end(lexer)) {
        return '\0';
    }

    return lexer->source[lexer->current + 1];
}

static char advance(ck_lexer *lexer) {
    char c = peek(lexer);
    lexer->current++;
    if (c == '\n') {
        lexer->line++;
    }

    return c;
}

static bool match(ck_lexer *lexer, char c) {
    if (peek(lexer) == c) {
        advance(lexer);
        return true;
    }

    return false;
}

static void skip_whitespace(ck_lexer *lexer) {
    while (true) {
        char c = peek(lexer);
        if (isspace(c)) {
            advance(lexer);
        } else if (c == '#') {
            /* '#' is the start of a comment,
             *  therefore we ignore the rest of the line.
             */
            while (peek(lexer) != '\n' && !is_at_end(lexer)) {
                advance(lexer);
            }
        } else {
            return;
        }
    }
}

static ck_token_type lex_number(ck_lexer *lexer) {
    while (isdigit(peek(lexer))) {
        advance(lexer);
    }

    if (peek(lexer) == '.' && isdigit(peek_next(lexer))) {
        /* Consume the period. */
        advance(lexer);

        while (isdigit(peek(lexer))) {
            advance(lexer);
        }
    }

    return CK_TOK_NUMBER;
}

static ck_token_type lex_string(ck_lexer *lexer) {
    while (peek(lexer) != '"' && !is_at_end(lexer)) {
        advance(lexer);
    }

    /* A second quote was never found and
     * therefore the string is unterminated.
     */
    if (is_at_end(lexer)) {
        return CK_TOK_ERR_UNTERMINATED_STRING;
    }

    /* Consume the second quote. */
    advance(lexer);

    return CK_TOK_STRING;
}

typedef struct keyword_pair {
    ck_token_type type;
    char *name;
    size_t name_len;
} keyword_pair;

static const keyword_pair keywords[] = {
    {CK_TOK_AND, "and", 3},     {CK_TOK_OR, "or", 2},
    {CK_TOK_NOT, "not", 3},     {CK_TOK_IF, "if", 2},
    {CK_TOK_ELSE, "else", 4},   {CK_TOK_ELIF, "elif", 4},
    {CK_TOK_FN, "fn", 2},       {CK_TOK_VAR, "var", 3},
    {CK_TOK_FOR, "for", 3},     {CK_TOK_IN, "in", 2},
    {CK_TOK_WHILE, "while", 5}, {CK_TOK_TRUE, "true", 4},
    {CK_TOK_FALSE, "false", 5}, {CK_TOK_NONE, "none", 4},
    {CK_TOK_BREAK, "break", 5}, {CK_TOK_RETURN, "return", 6},
};

static ck_token_type lex_identifier(ck_lexer *lexer) {
    while (isalpha(peek(lexer)) || isdigit(peek(lexer) || peek(lexer) == '_')) {
        advance(lexer);
    }

    const char *lexeme = lexer->source + lexer->start;
    size_t lexeme_length = lexer->current - lexer->start;

    /* TODO: Linear search was chosen for simplicity,
     * but a hashmap or trie might be faster.
     */
    for (size_t i = 0; i < CK_ARRAY_LENGTH(keywords); i++) {
        const keyword_pair pair = keywords[i];
        if (pair.name_len != lexeme_length) {
            continue;
        }

        if (memcmp(pair.name, lexeme, pair.name_len) == 0) {
            return pair.type;
        }
    }

    return CK_TOK_IDENTIFIER;
}

static ck_token_type next_type(ck_lexer *lexer) {
    skip_whitespace(lexer);
    lexer->start = lexer->current;

    if (is_at_end(lexer)) {
        return CK_TOK_END_OF_FILE;
    }

    char c = advance(lexer);
    if (isdigit(c)) {
        return lex_number(lexer);
    }

    if (isalpha(c) || c == '_') {
        return lex_identifier(lexer);
    };

    switch (c) {
    case '(':
        return CK_TOK_LPAREN;
    case ')':
        return CK_TOK_RPAREN;
    case '{':
        return CK_TOK_LBRACE;
    case '}':
        return CK_TOK_RBRACE;
    case '[':
        return CK_TOK_LBRACKET;
    case ']':
        return CK_TOK_RBRACKET;
    case ',':
        return CK_TOK_COMMA;
    case '.':
        return CK_TOK_DOT;
    case '~':
        return CK_TOK_TILDE;
    case ';':
        return CK_TOK_SEMICOLON;
    case ':':
        return CK_TOK_COLON;
    case '-':
        if (match(lexer, '=')) {
            return CK_TOK_MINUS_EQUAL;
        } else {
            return CK_TOK_MINUS;
        }
    case '+':
        if (match(lexer, '=')) {
            return CK_TOK_PLUS_EQUAL;
        } else {
            return CK_TOK_PLUS;
        }
    case '/':
        if (match(lexer, '=')) {
            return CK_TOK_SLASH_EQUAL;
        } else {
            return CK_TOK_SLASH;
        }
    case '*':
        if (match(lexer, '=')) {
            return CK_TOK_STAR_EQUAL;
        } else {
            return CK_TOK_STAR;
        }
    case '!':
        if (match(lexer, '=')) {
            return CK_TOK_BANG_EQUAL;
        } else {
            return CK_TOK_BANG;
        }
    case '=':
        if (match(lexer, '=')) {
            return CK_TOK_EQUAL_EQUAL;
        } else {
            return CK_TOK_EQUAL;
        }
    case '>':
        if (match(lexer, '=')) {
            return CK_TOK_GREATER_EQUAL;
        } else {
            return CK_TOK_GREATER;
        }
    case '<':
        if (match(lexer, '=')) {
            return CK_TOK_LESS_EQUAL;
        } else {
            return CK_TOK_LESS;
        }
    case '"':
        return lex_string(lexer);
    }

    return CK_TOK_ERR_UNEXPECTED_CHAR;
}

void ck_lexer_init(ck_lexer *lexer, const char *source) {
    assert(lexer != NULL);
    assert(source != NULL);

    lexer->source = source;
    lexer->start = 0;
    lexer->current = 0;
    lexer->line = 1;
}

ck_token ck_lexer_next(ck_lexer *lexer) {
    assert(lexer != NULL);

    ck_token_type type = next_type(lexer);
    ck_token result = {.type = type,
                       .start = lexer->start,
                       .length = lexer->current - lexer->start,
                       .line = lexer->line};

    return result;
}
