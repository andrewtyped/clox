#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

/**
 * @brief Provides storage for constant values that appear in a lox program.
 * 
 */
typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);

#endif