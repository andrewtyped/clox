#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "table.h"
#include "object.h"
#include "value.h"

/**
 * @brief The maximum depth of the call stack.
 * 
 */
#define FRAMES_MAX 64


/**
 * @brief Constant defining the max depth of a stack in VM. 
 * 
 */
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef struct {
    ObjClosure* closure;
    uint8_t* ip;
    Value* slots;
} CallFrame;

typedef struct {
    /**
     * @brief The call stack of functions
     * 
     */
    CallFrame frames[FRAMES_MAX];

    /**
     * @brief The depth of the call stack;
     * 
     */
    int frameCount;

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
     * @brief Keep a hash table of global variable names and their values.
     * 
     */
    Table globals;

    /**
     * @brief Keep a hash table of distinct strings in the program for interning.
     * 
     */
    Table strings;

    /**
     * @brief A list of closed values stored on the heap.
     * 
     */
    ObjUpvalue* openUpvalues;

    /**
     * @brief The total number of bytes of managed memory allocated by the VM.
     * 
     */
    size_t bytesAllocated;

    /// @brief  Trigger garbage collection when bytesAllocated reaches this value.
    size_t nextGC;

/**
 * @brief Points to the head of a list containing all objects allocated in the program.
 * 
 */
    Obj* objects;

    int grayCount;
    int grayCapacity;
    /**
     * @brief The worklist garbage collection uses to determine which objects cannot be freed.
     * 
     */
    Obj** grayStack;
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