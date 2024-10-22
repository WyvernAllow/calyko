#ifndef CK_TOKEN_TYPE
#define CK_TOKEN_TYPE

typedef enum ck_token_type {
    CK_TOK_LPAREN,                  
    CK_TOK_RPAREN,                  
    CK_TOK_LBRACE,                  
    CK_TOK_RBRACE,                  
    CK_TOK_LBRACKET,                
    CK_TOK_RBRACKET,                
    CK_TOK_COMMA,                   
    CK_TOK_DOT,                     
    CK_TOK_TILDE,                   
    CK_TOK_SEMICOLON,               
    CK_TOK_COLON,                   

    CK_TOK_MINUS,
    CK_TOK_MINUS_EQUAL,
    CK_TOK_PLUS,
    CK_TOK_PLUS_EQUAL,
    CK_TOK_SLASH,
    CK_TOK_SLASH_EQUAL,
    CK_TOK_STAR,
    CK_TOK_STAR_EQUAL,
    CK_TOK_BANG,
    CK_TOK_BANG_EQUAL,
    CK_TOK_EQUAL,
    CK_TOK_EQUAL_EQUAL,
    CK_TOK_GREATER,
    CK_TOK_GREATER_EQUAL,
    CK_TOK_LESS,
    CK_TOK_LESS_EQUAL,  

    CK_TOK_IDENTIFIER,
    CK_TOK_STRING,
    CK_TOK_NUMBER,

    CK_TOK_AND,
    CK_TOK_OR,
    CK_TOK_NOT,
    CK_TOK_IF,
    CK_TOK_ELSE,
    CK_TOK_ELIF,
    CK_TOK_FN,
    CK_TOK_VAR,
    CK_TOK_FOR,
    CK_TOK_IN,
    CK_TOK_WHILE,
    CK_TOK_TRUE,
    CK_TOK_FALSE,
    CK_TOK_NONE,
    CK_TOK_BREAK,
    CK_TOK_RETURN,

    CK_TOK_END_OF_FILE,

    CK_TOK_ERR_UNEXPECTED_CHAR,
    CK_TOK_ERR_UNTERMINATED_STRING,

    CK_TOKEN_TYPE_COUNT,
} ck_token_type;

const char *ck_token_type_str(ck_token_type type);

#endif /* CK_TOKEN_TYPE */
