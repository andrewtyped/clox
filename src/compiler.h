#ifndef clox_compiler_h
#define clox_compiler_h

#include "vm.h"

/**
 * @brief Compiles lox source code to clox byte code.
 * 
 */
bool compile(const char* source, Chunk* chunk);

#endif