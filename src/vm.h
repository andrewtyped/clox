#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

/**
 * @brief Constant defining the max depth of a stack in VM. 
 * 
 */
#define STACK_MAX 256

typedef struct {
    /**
     * @brief Pointer to the current chunk the VM is executing.
     * 
     */
    Chunk* chunk;

    /**
     * @brief pointer to the NEXT instruction to execute.
     * 
     */
    uint8_t* ip;

    /**
     * @brief The stack of values currently in scope for the chunk.
     * 
     */
    Value stack[STACK_MAX];

    /**
     * @brief Pointer to the address just after the top value of the stack. Allows us to represent an empty stack by pointing to element 0 of stack.
     * 
     */
    Value* stackTop;

/**
 * @brief Points to the head of a list containing all objects allocated in the program.
 * 
 */
    Obj* objects;
} VM;

/**
 * @brief labels the result of interpreting a chunk. Used to set exit code of the clox compiler.
 * 
 */
typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

/**
 * @brief Allocates resources for the global vm instance.
 * 
 */
void initVM();

/**
 * @brief Frees resources for the global vm instance.
 * 
 */
void freeVM();

/**
 * @brief Executes the code instructions in a chunk.
 */
InterpretResult interpret(const char* source);

void push(Value value);
Value pop();

#endif