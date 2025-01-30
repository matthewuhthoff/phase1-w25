/* custom_regex.h*/

#ifndef REGEX_H
#define REGEX_H

#include "tokens.h"
#include <regex.h>

extern const char *patterns[TOKEN_COUNT]; // Array of regex patterns for each token type

void compile_patterns(regex_t regexArray[] ); // Compile patterns into regex_t structures
void free_patterns(regex_t regexArray[]); // Free memory allocated for patterns


#endif /* REGEX_H */