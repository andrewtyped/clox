#include <stdio.h>
#include <string.h>

#include "common.h"
#include "scanner.h"

/**
 * @brief Tracks progress while scanning lox code.
 * 
 */
typedef struct {
    /**
     * @brief Pointer to the start of the current lexeme.
     * 
     */
    const char* start;

    /**
     * @brief Pointer to the next character to consume.
     * 
     */
    const char* current;

    /**
     * @brief Identifies the current line number in source code. newline advances the line number.
     * 
     */
    int line;
} Scanner;

Scanner scanner;

void initScanner(const char* source) {
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

Token scanToken() {
    scanner.start = scanner.current;
    Token token = {};
    token.type = TOKEN_EOF;
    token.start = 0;
    token.length = 0;
    token.line = 0;
    return token;
}