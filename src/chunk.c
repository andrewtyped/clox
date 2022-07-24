#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, 
                                 chunk->code,
                                 oldCapacity,
                                 chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void writeConstant(Chunk* chunk, 
                   Value value, 
                   int line) {
    int constantIndex = addConstant(chunk, value);

    bool isLongConstant = constantIndex > UINT8_MAX_VALUE 
        ? true
        : false;

    if(isLongConstant) {
        //Our long constant is assumed to be 24 bits - three operands (one byte each).

        //mask the lower 4 bits. Shift masked value right 16 bits to fit into 8 bits.
        uint8_t operand1 = ((unsigned)constantIndex & 0x00ff0000) >> 16;

        //mask the upper 2 and lower 2 bits. Shift masked value right 8 bits to fit into 8 bits.
        uint8_t operand2 = ((unsigned)constantIndex & 0x0000ff00) >> 8;

        //mask the upper 4 bits. No shifting required.
        uint8_t operand3 = (unsigned)constantIndex & 0x000000ff;

        writeChunk(chunk, OP_CONSTANT_LONG, line);
        writeChunk(chunk, operand1, line);
        writeChunk(chunk, operand2, line);
        writeChunk(chunk, operand3, line);
    } else {
        writeChunk(chunk, OP_CONSTANT, line);
        writeChunk(chunk, constantIndex, line);
    }


                   }