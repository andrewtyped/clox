#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

/**
 * @brief See docs/opcodes.md for detailed information about op codes.
 * 
 */
typedef enum {
    OP_CONSTANT = 0x00,
    OP_CONSTANT_LONG = 0x01,
    OP_RETURN = 0x02
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

/**
 * @brief Adds a byte to a chunk, and records the line number in source code where the byte originated from. The byte may be either an op code or an operand for an op code.
 * 
 * @param chunk 
 * @param byte 
 * @param line 
 */
void writeChunk(Chunk* chunk, uint8_t byte, int line);

/**
 * @brief Adds a constant value to a chunk
 * 
 * @param chunk The chunk to add the constant to
 * @param value the value of the constant
 * @return int The index of the constant in chunk's value array.
 */
int addConstant(Chunk* chunk, Value value);

/**
 * @brief Adds a constant value to the chunk and adds an operation to the chunk's code to load the constant. The operation chosen will be OP_CONSTANT or OP_CONSTANT_LONG, depending on how many constants have already been added to the chunk.
 * 
 * @param chunk The chunk which will host the constant.
 * @param value The value of the constant to add.
 * @param line The line number in source code from which the constant originated.
 */
void writeConstant(Chunk* chunk, 
                   Value value, 
                   int line);

#endif