#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_RETURN
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;

    /**
     * @brief Stores the line number for each instruction in the chunk.
     * 
     */
    int* lines;

    /**
     * @brief Stores literal values
     * contained in this chunk.
     */
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);

int addConstant(Chunk* chunk, Value value);


#endif