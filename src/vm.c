#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "value.h"
#include "vm.h"

VM vm;

static void resetStack() {
    vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

void freeVM() {
}

void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

/**
 * @brief Execute the instructions in the global vm instance.
 * 
 * @return InterpretResult 
 */
static InterpretResult run() {
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
        
        for(;;) {

        #ifdef DEBUG_TRACE_EXECUTION
            printf("          ");
            for(Value* slot = vm.stack; slot < vm.stackTop; slot++) {
                printf("[ ");
                printValue(*slot);
                printf(" ]");
            }

            printf("\n");
            disassembleInstruction(vm.chunk,
            //convert ip back into offset index from chunk start point.
            (int)(vm.ip - vm.chunk-> code));

        #endif
            uint8_t instruction;
            switch (instruction = READ_BYTE()) {
                case OP_CONSTANT: {
                    Value constant = READ_CONSTANT();
                    push(constant);
                    break;
                }
                case OP_CONSTANT_LONG: {
                    //TODO: implement this
                    printf("YOU FORGOT TO IMPLEMENT OP_CONSTANT_LONG");
                    break;
                }
                case OP_NEGATE: {
                    push(-pop());
                    break;
                }
                case OP_RETURN: {
                    printValue(pop());
                    printf("\n");
                    return INTERPRET_OK;
                }
            }
        }

    #undef READ_BYTE
    #undef READ_CONSTANT
    
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}
