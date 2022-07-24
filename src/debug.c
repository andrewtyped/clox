#include <stdio.h>

#include "debug.h"
#include "value.h"

/**
 * @brief Print the value of an OP_CONSTANT instruction
 * 
 */
static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];

    //Print "OP_CONSTANT" followed by the index of the constant in the chunk's values, followed by the constant value stored at that index.
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
}

/**
 * @brief Print the value of an OP_CONSTANT_LONG instruction
 * 
 */
static int longConstantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constantIdx1 = chunk->code[offset + 1];
    uint8_t constantIdx2 = chunk->code[offset + 2];
    uint8_t constantIdx3 = chunk->code[offset + 3];

    int constant = constantIdx1 * 256 * 256 + constantIdx2 * 256 + constantIdx3;

    //Print "OP_CONSTANT" followed by the index of the constant in the chunk's values, followed by the constant value stored at that index.
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 4;
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    for(int offset = 0; offset < chunk->count;) {

        offset = disassembleInstruction(chunk, offset);
    }
}

int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);

    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset -1]) {
        printf("   | ");
    } else {
        printf("%4d ", chunk->lines[offset]);
    }

    uint8_t instruction = chunk->code[offset];

    switch (instruction) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_CONSTANT_LONG:
            return longConstantInstruction("OP_CONSTANT_LONG", chunk, offset);
        case OP_NEGATE:
            return simpleInstruction("OP_NEGATE", offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}