#ifndef clox_value_h
#define clox_value_h

#include "string.h"
#include "common.h"

typedef struct Obj Obj;
typedef struct ObjString ObjString;

#ifdef NAN_BOXING

//Sets the sign bit of an IEEE 754 floating point number to 1. In lox, a sign bit of 1 indicates an object. A sign bit of 0 indicates everything else.
#define SIGN_BIT ((uint64_t)0x8000000000000000)

//IEEE 754 specifies a double having all 11 exponent bits set, with a 0 bit for thie highest mantissa bit, is a "quiet NaN" value, like infinity or, in our case, nil, bool, and pointers. Binary representation is 01111111111111000...00 (0's are the last 50 bits of the double.) We are also setting an additional bit to avoid a special Intel quiet NaN.
#define QNAN ((uint64_t)0x7ffc000000000000)

#define TAG_NIL 1 // 01.
#define TAG_FALSE 2 // 10.
#define TAG_TRUE 3 // 11.

typedef uint64_t Value;

#define IS_BOOL(value)   (((value) | 1) == TRUE_VAL)
#define IS_NIL(value)    ((value) == NIL_VAL)
#define IS_OBJ(value) \
    (((value) & (QNAN | SIGN_BIT)) == (QNAN | SIGN_BIT))
//A normal number WON'T have all its exponent bits set, so and-ing it with QNAN will produce a value other than QNAN.
#define IS_NUMBER(value) (((value) & QNAN) != QNAN)

#define AS_BOOL(value)   ((value) == TRUE_VAL)
#define AS_NUMBER(value) valueToNum(value)
#define AS_OBJ(value) \
    ((Obj*)(uintptr_t)((value) & ~(SIGN_BIT | QNAN)))

#define NUMBER_VAL(num) numToValue(num)
#define OBJ_VAL(obj) \
    (Value)(SIGN_BIT | QNAN | (uint64_t)(uintptr_t)(obj))
#define BOOL_VAL(b)       ((b) ? TRUE_VAL : FALSE_VAL)
#define FALSE_VAL         ((Value)(uint64_t)(QNAN | TAG_FALSE))
#define TRUE_VAL         ((Value)(uint64_t)(QNAN | TAG_TRUE))
#define NIL_VAL         ((Value)(uint64_t)(QNAN | TAG_NIL))

static inline double valueToNum(Value value) {
    double num;
    memcpy(&num, &value, sizeof(Value));
    return num;
}

static inline Value numToValue(double num) {
    Value value;
    memcpy(&value, &num, sizeof(double));
    return value;
}

#else

typedef enum {
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER,
    VAL_OBJ
} ValueType;

typedef struct {
    ValueType type;
    union {
        bool boolean;
        double number;
        Obj* obj;
    } as;
} Value;

//These enums are using struct initializer syntax to build a Value instance.
//The .boolean / .number thing must just be short-hand for initializing the "as" union.
#define BOOL_VAL(value)     ((Value){VAL_BOOL, {.boolean = value}})
#define NIL_VAL             ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUMBER, {.number = value}})
#define OBJ_VAL(value)    ((Value){VAL_OBJ, {.obj = (Obj*)value}})

#define AS_BOOL(value)    ((value).as.boolean)
#define AS_NUMBER(value)  ((value).as.number)
#define AS_OBJ(value)     ((value).as.obj)

#define IS_BOOL(value)    ((value).type == VAL_BOOL)
#define IS_NIL(value)     ((value).type == VAL_NIL)
#define IS_NUMBER(value)  ((value).type == VAL_NUMBER)
#define IS_OBJ(value)      ((value).type == VAL_OBJ)

#endif

/**
 * @brief Provides storage for constant values that appear in a lox program.
 * 
 */
typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

bool valuesEqual(Value a, Value b);
void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);

void printValue(Value value);

#endif