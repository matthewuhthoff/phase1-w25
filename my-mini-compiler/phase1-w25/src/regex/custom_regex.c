/* custom_regex.c */

#include "tokens.h"
#include <regex.h>
#include "custom_regex.h"

const char *patterns[TOKEN_COUNT] = {
    "^if|^repeat|^until",              // Keywords
    "^[a-zA-Z_][a-zA-Z0-9_]*",       // Identifiers
    "^\"([^\"\\\\]|^\\\\.)*\"",       // String literals
    "^==|^!=|^<=|^>=|^&&|^\\|^\\||^\\+|^\\-|^\\*|^\\/|^=|^<|^>|^!", // Operators
    "^[{}(),;]",                     // Punctuation
    "^[0-9]+(\\.[0-9]+)?",           // Numbers
    "^ ",
    "^\r\n|^\r|^\n"
    // "\\s+|//.*|/\\*[^]*?\\*/"       // Whitespace and comments (ignored)
};

void compile_patterns(regex_t regexArray[]) {
    for (int i = 0; i < TOKEN_COUNT; i++) {
        regcomp(&regexArray[i], patterns[i], REG_EXTENDED); // Compile the pattern and save em to cache
    }
}

void free_patterns(regex_t regexArray[]) {
    for (int i = 0; i < TOKEN_COUNT; i++) {
        regfree(&regexArray[i]); // Free the memory allocated for the pattern
    }
}


TokenType get_longest_match(regmatch_t pmatch[TOKEN_COUNT][1], bool matches[TOKEN_COUNT], int* length)
{
    int longest_token;
    int longest = 0;
    int cur;
    for (int i = 0; i < TOKEN_COUNT; ++i) {
        if (!matches[i]) {
            continue;
        }
        cur = pmatch[i][0].rm_eo - pmatch[i][0].rm_so;
        if (cur > longest) {
            longest = cur;
            longest_token = i;
        }
    }
    *length = longest;
    return longest_token;
}

