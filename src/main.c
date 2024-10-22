#include <stdio.h>
#include <stdbool.h>

#include "lexer.h"

#define CK_REPL_BUFSIZE 256

static void repl(void) {
    char buffer[CK_REPL_BUFSIZE];
    
    while(true) {
        printf("> ");

        if(!fgets(buffer, sizeof(buffer), stdin)) {
            printf("\n");
            break;
        }

        ck_lexer lexer;
        ck_lexer_init(&lexer, buffer);

        ck_token next = ck_lexer_next(&lexer);
        while(next.type != CK_TOK_END_OF_FILE) {
            const char *slice = lexer.source + next.start;
            printf("type: %s \n\tlexeme: %.*s \n\tln: %zu\n",
                ck_token_type_str(next.type),
                (int)next.length,
                slice,
                next.line
            );

            next = ck_lexer_next(&lexer);
        }
    }
}

int main(void) {
    repl();
}
