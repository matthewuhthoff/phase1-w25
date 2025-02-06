#ifndef ERRORS_H
#define ERRORS_H

#include "tokens.h"

/* Function declarations */

/**
 * Print a lexical error message to stderr
 * @param error The type of lexical error
 * @param line The line number where the error occurred
 * @param lexeme The problematic text
 */
void print_lexical_error(ErrorType error, int line, const char *lexeme);

/**
 * Print a system error message to stderr
 * @param error The type of system error
 * @param msg Additional error details
 */
void print_system_error(SysErrorType error, const char * msg, ...);

#endif
