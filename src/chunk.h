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
    OP_RETURN = 0x02,
    OP_NEGATE = 0x03,
    OP_ADD = 0x04,
    OP_SUBTRACT = 0x05,
    OP_MULTIPLY = 0x06,
    OP_DIVIDE = 0x07,
    OP_NIL = 0x08,
    OP_TRUE = 0x09,
    OP_FALSE = 0x0A,
    OP_NOT = 0x0B,
    OP_EQUAL = 0x0C,
    OP_GREATER = 0x0D,
    OP_LESS = 0x0E,
    OP_PRINT = 0x0F,
    OP_POP = 0x10,
    OP_DEFINE_GLOBAL = 0x11,
    OP_GET_GLOBAL = 0x12,
    OP_SET_GLOBAL = 0x13,
    OP_GET_LOCAL = 0x14,
    OP_SET_LOCAL = 0x15,
    OP_JUMP_IF_FALSE = 0x16,
    OP_JUMP = 0x17,
    OP_LOOP = 0x18,
    OP_CALL = 0x19,
    OP_CLOSURE = 0x1A,
    OP_GET_UPVALUE = 0x1B,
    OP_SET_UPVALUE = 0x1C,
    OP_CLOSE_UPVALUE = 0x1D
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;

    /**
     * @brief Stores the line number for each instruction in the chunk.
     * 
     * TODO: Use run-length encoding to improve space usage for line number tracking. (See ch. 14 challenges).
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