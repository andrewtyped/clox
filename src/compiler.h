#ifndef clox_compiler_h
#define clox_compiler_h

#include "object.h"
#include "vm.h"

/**
 * @brief Compiles lox source code to clox byte code.
 * 
 */
ObjFunction* compile(const char* source);

void markCompilerRoots();

#endif