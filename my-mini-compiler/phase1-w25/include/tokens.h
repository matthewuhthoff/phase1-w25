//
// Created by Youssef
//

/* tokens.h */
#ifndef TOKENS_H
#define TOKENS_H
#define TOKEN_COUNT 8  // 8 tokens we're using
#define MAX_TOKEN_SIZE 100
/* Token types that need to be recognized by the lexer
 * TODO: Add more token types as per requirements:
 * - Keywords or reserved words (if, repeat, until)
 * - Identifiers
 * - String literals
 * - More operators
 * - Delimiters
 */

typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_OPERATOR,   // e.g., "+", "-"
    TOKEN_PUNCTUATION,   // e.g., "{", "}", ",", ".", "(", ")"
    TOKEN_NUMBER,
    TOKEN_WHITESPACE,
    TOKEN_NEWLINE,
    TOKEN_NONE
} TokenType;


/* Error types for lexical analysis
 * TODO: Add more error types as needed for your language - as much as you like !!
 */
typedef enum {
    ERROR_NONE,
    ERROR_INVALID_CHAR,
    ERROR_INVALID_NUMBER,
    ERROR_CONSECUTIVE_OPERATORS,
    ERROR_OVERSIZED_TOKEN
} ErrorType;

typedef enum {
    ERROR_FILE,
    ERROR_ARGS,
    ERROR_REGEX
} SysErrorType;
/* Token structure to store token information
 * TODO: Add more fields if needed for your implementation
 * Hint: You might want to consider adding line and column tracking if you want to debug your lexer properly.
 * Don't forget to update the token fields in lexer.c as well
 */
typedef struct {
    TokenType type;
    char lexeme[MAX_TOKEN_SIZE];   // Actual text of the token
    int line;           // Line number in source file
    ErrorType error;    // Error type if any
} Token;


#endif /* TOKENS_H */
