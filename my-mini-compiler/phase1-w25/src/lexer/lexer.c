/* lexer.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/tokens.h"
#include "../../include/custom_regex.h"
#include "../../include/errors.h"

// Line tracking
static int current_line = 1;

void print_token(Token token) {
    printf("Token: ");
    switch (token.type) {
        case TOKEN_KEYWORD:
            printf("KEYWORD");
            break;
        case TOKEN_IDENTIFIER:
            printf("IDENTIFIER");
            break;
        case TOKEN_STRING:
            printf("STRING");
            break;
        case TOKEN_OPERATOR:
            printf("OPERATOR");
            break;
        case TOKEN_PUNCTUATION:
            printf("PUNCTUATION");
            break;
        case TOKEN_NUMBER:
            printf("NUMBER");
            break;
        case TOKEN_WHITESPACE:
            printf("WHITESPACE");
            break;
        case TOKEN_NEWLINE:
            printf("NEWLINE");
            break;
        case TOKEN_NONE:
            printf("NO TOKEN");
            break;
        default:
            printf("UNKNOWN Token\n");
    }
    const char * lexeme = token.lexeme;
    if(strcmp(lexeme, "\n") == 0)
    {
        lexeme = "\\n"; // Better output for newline chars
    }
    printf(" | Lexeme: '%s' | Line: %d\n", lexeme, token.line);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        print_system_error(ERROR_ARGS, "Must pass exactly one file to parse");
        return 1;
    }

    char *file_buffer;
    size_t file_size;
    FILE *fp;

    fp = fopen(argv[1], "r");
    if (!fp) {
        print_system_error(ERROR_ARGS, "Invalid file path: %s", argv[1]);
        return 1;
    } 
    
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);

    file_buffer = (char *)malloc(file_size + 1);
    if (!file_buffer) {
        print_system_error(ERROR_FILE, "file AT %s is null", argv[1]);
        free(file_buffer);
        fclose(fp);
        return 1;
    }
    memset(file_buffer, 0, file_size + 1);  // initialize file_buffer to null
    size_t bytes_read = fread(file_buffer, 1, file_size, fp);

    if (bytes_read != file_size) {
        print_system_error(ERROR_FILE, "Could not read the whole file");
        fclose(fp);
        free(file_buffer);
        return 1;
    }
    fclose(fp);

    printf("Analyzing input:\n%s\n\n", file_buffer);
    
    regex_t regex[TOKEN_COUNT];
    regmatch_t pmatch[TOKEN_COUNT][1];

    bool matches[TOKEN_COUNT] = { false };
    bool match, any_match;
    Token cur_token = {TOKEN_NONE, "", current_line, ERROR_NONE};
    TokenType cur_match;
    int cur_longest;
    size_t cur_position = 0;
    
    char* input_buffer = file_buffer;

    compile_patterns(regex);
    do {
        any_match = false;
        for (int i = 0; i < TOKEN_COUNT; ++i) {
            match = !regexec(&regex[i], input_buffer, 1, pmatch[i], 0);  // Invert logic on return value
            matches[i] = match;
            any_match |= match;
        }
        if (any_match) {
            cur_match = get_longest_match(pmatch, matches, &cur_longest);
            cur_token.type = cur_match;
            cur_token.line = current_line;
            cur_token.error = ERROR_NONE;
            if (cur_longest < MAX_TOKEN_SIZE) {
                memcpy(cur_token.lexeme,
                       input_buffer,
                       cur_longest);  // huge bug if identifier is longer than 100 chars

                print_token(cur_token);
            } else {
                print_lexical_error(ERROR_OVERSIZED_TOKEN, current_line,  cur_token.lexeme);
                memcpy(cur_token.lexeme,
                       input_buffer,
                       MAX_TOKEN_SIZE-1);
                print_token(cur_token); // Problematic but sorta fixes this?
            }
            if (cur_match == TOKEN_NEWLINE) {  // really don't like doing this here
                ++current_line;
            }

            input_buffer += cur_longest;
            cur_position += cur_longest;
        } else {
            print_system_error(ERROR_REGEX, "No patterns match the token here: %d", *input_buffer);
            input_buffer += 1;  // increment ptr and try again
            cur_position += 1;
            if(*input_buffer == '\0')
            {
                print_system_error(ERROR_FILE, "Error parsing empty file");
                break;
            }  // Kill if EOF, happens in empty files
        }
        memset(matches, 0, sizeof(matches));  // reset matches;
        cur_token.type = TOKEN_NONE;  // reset current token
        memset(cur_token.lexeme, 0, MAX_TOKEN_SIZE);
        cur_token.error = ERROR_NONE;
    } while(cur_position <= file_size - 1);  // -1 for EOF char

    free_patterns(regex);
    free(file_buffer);
    return 0;
}
