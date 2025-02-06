#include <stdio.h>
#include <stdarg.h>
#include "../../include/tokens.h"
#include "../../include/errors.h"

void print_lexical_error(ErrorType error, int line, const char *lexeme) {
    fprintf(stderr, "Lexical Error at line %d: ", line);
    switch (error) {
        case ERROR_INVALID_CHAR:
            fprintf(stderr,"Invalid character '%s'\n", lexeme);
            break;
        case ERROR_INVALID_NUMBER:
            fprintf(stderr, "Invalid number format\n");
            break;
        case ERROR_CONSECUTIVE_OPERATORS:
            fprintf(stderr, "Consecutive operators not allowed\n");
            break;
        case ERROR_OVERSIZED_TOKEN:
            // Not sure what else to put other than forbidden/not allowed
            fprintf(stderr, "Token exceeds %d characters, this is forbidden. Truncated to %d characters\n", 
                (MAX_TOKEN_SIZE-1), (MAX_TOKEN_SIZE-1));
            break;
        default:
            fprintf(stderr,"Unknown error\n");
    }
}

void print_system_error(SysErrorType error, const char * msg, ...) {
    char formatted_msg[128];
    va_list args;
    va_start(args, msg);
    vsnprintf(formatted_msg, 128, msg, args);
    va_end(args);

    fprintf(stderr, "System Error: ");
    switch (error) {
        case ERROR_FILE:
            fprintf(stderr,"Handling File(s)\n");
            fprintf(stderr, "%s\n", formatted_msg);
            break;
        case ERROR_ARGS:
            fprintf(stderr, "Incorrect Args\n");
            fprintf(stderr, "%s\n", formatted_msg);
            break;
        case ERROR_REGEX:
            fprintf(stderr, "Regex Matching\n");
            fprintf(stderr, "%s\n", formatted_msg);
            break;
        default:
            fprintf(stderr,"Unknown error\n");
            break;
    }
}
