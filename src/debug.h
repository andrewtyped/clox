#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

/**
 * @brief Disassemble the op-codes and arguments in a chunk to human-readable text
 * 
 * @param chunk The chunk to disassemble
 * @param name The name of the chunk, used to distinguish it from other chunks.
 */
void disassembleChunk(Chunk* chunk, const char* name);

/**
 * @brief Disassembly a single instruction and its parameters in a chunk.
 * 
 * @param chunk The chunk containing the instruction to disassemble.
 * @param offset The position of the instruction to disassemble within the chunk.
 * @return int The position (offset) of the next instruction to be disassembled.
 */
int disassembleInstruction(Chunk* chunk, int offset);

#endif