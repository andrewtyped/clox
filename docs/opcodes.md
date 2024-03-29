clox Op Codes
==============

Each op code is one byte, and accepts 0 or more operands. Each operand is one byte. If one byte is insufficient to hold the data in an operand, multiple bytes may be composed to form a logical operand. In this case, the operands are stored with a big-endian scheme (most significant byte first).

OP_CONSTANT
-----------

Loads a constant value from the current chunk. Supports up to 256 constants per chunk.

OpCode: 0x00
Operands:
- 0: index of constant to load

OP_CONSTANT_LONG
----------------

Loads a constant value from the current chunk. Supports up to 16,777,216 constants per chunk by storing the index to the constant as three operands.

OpCode: 0x01
Operands:
- 0: index of constant to load, byte 1
- 1: index of constant to load, byte 2
- 2: index of constant to load, byte 3

OP_RETURN
---------

OpCode: 0x02
Operands: None

OP_NEGATE
---------

Performs unary negation on the value on top of the stack.

OpCode: 0x03
Operands: None

OP_ADD
------

Performs binary addition of the two elements on top of the stack. The first operand is top of stack. Second operand is next element down.

OpCode: 0x04
Operands: None

OP_SUBTRACT
-----------

Performs binary subtraction of the two elements on top of the stack. The first operand is top of stack. Second operand is next element down.

OpCode: 0x05
Operands: None

OP_MULTIPLY
-----------

Performs binary multiplication of the two elements on top of the stack. The first operand is top of stack. Second operand is next element down.

OpCode: 0x06
Operands: None

OP_DIVIDE
---------

Performs divide addition of the two elements on top of the stack. The first operand is top of stack. Second operand is next element down.

OpCode: 0x07
Operands: None

OP_NIL
------

Pushes a nil value onto the stack.

OpCode: 0x08
Operands: None

OP_TRUE
-------

Pushes a true value onto the stack.

OpCode: 0x09
Operands: None

OP_FALSE
--------

Pushes a false value onto the stack.

OpCode: 0x0A
Operands: None

OP_NOT
--------

Logically negate the value on top of the stack.

OpCode: 0x0B
Operands: None

OP_EQUAL
--------

Compares the two values on top of the stack. If they are equal, pushes true onto the stack. Otherwise, pushes false onto the stack.

OpCode: 0x0C
Operands: None

OP_GREATER
--------

Compares the two values on top of the stack. If the top value is greater than the penultimate value, pushes true onto the stack. Otherwise, pushes false onto the stack.

OpCode: 0x0D
Operands: None

OP_LESS
--------

Compares the two values on top of the stack. If the top value is less than the penultimate value, pushes true onto the stack. Otherwise, pushes false onto the stack.

OpCode: 0x0E
Operands: None

OP_PRINT
--------

Evaluates an expression and writes its result to stdout.

OpCode: 0x0F
Operands: None

OP_POP
------

Pop the top value off the stack. This effectively discards the value.

OpCode: 0x10
Operands: None

OP_DEFINE_GLOBAL
------

Defines a new global variable.

OpCode: 0x11
Operands:
    - 0: Index of the constant holding the variable's name.

OP_GET_GLOBAL
-------------

Gets the value of a global variable.

OpCode: 0x12
Operants:
    - 0: Index of the constant holding the variable's name;

OP_SET_GLOBAL
-------------

Sets the value of a global variable.

OpCode: 0x13
Operants:
    - 0: Index of the constant holding the variable's name;

OP_GET_LOCAL
-------------

Gets the value of a local variable by pushing the value of the stack slot where the local was defined on top of the stack.

OpCode: 0x14
Operants:
    - 0: Index of the stack slot hosting the local.

OP_SET_LOCAL
-------------

Sets the value of a local variable by modifying the value of the stack slot hosting the variable.

OpCode: 0x15
Operants:
    - 0: Index of the stack slot hosting the local.

OP_JUMP_IF_FALSE
----------------

Moves the instruction pointer if the value on top of the stack is falsey.

OpCode: 0x16
Operands:
    - 0: The number of bytes to jump (high byte)
    - 1: The number of bytes to jump (low byte)

OP_JUMP
-------

Moves the instruction pointer forward.

OpCode: 0x17
Operands:
    - 0: The number of bytes to jump (high byte)
    - 1: The number of bytes to jump (low byte)

OP_JUMP
-------

Moves the instruction pointer backward.

OpCode: 0x18
Operands:
    - 0: The number of bytes to jump back (high byte)
    - 1: The number of bytes to jump back (low byte)

OP_CALL
-------

Calls a function.

OpCode: 0x19
Operands:
    - 0: The number of arguments to the function.

OP_CLOSURE
-------

Defines a function.

OpCode: 0x1A
Operands:

Variable. For each upvalue captured by the closure, emits two bytes:
    - 0: 1 or 0. 1 if the variable is local to the enclosing function. 0 otherwise.
    - 1: The local slot or upvalue index to capture.

OP_GET_UPVALUE
---------------

Gets a variable from an enclosing scope

OpCode: 0x1B
Operands:
    - 0: ???

OP_SET_UPVALUE
---------------

Sets a variable from an enclosing scope

OpCode: 0x1C
Operands:
    - 0: ???

OP_CLOSE_UPVALUE
---------------

Hoists a closed variable onto the heap

OpCode: 0x1D
Operands: None

OP_CLASS
--------

Allocates memory for a new class and pushes the class onto the stack.

OpCode: 0x1E
Operands:
    - 0: The index of the constant containing the class's name.

OP_SET_PROPERTY
---------------

Assigns the value of a property in a class instance.

OpCode: 0x1F
Operands:
    - 0: The index of the constant hosting the property's name.

OP_GET_PROPERTY
---------------

Retrieves the value of a property in a class instance.

OpCode: 0x20
Operands:
    - 0: The index of the constant hosting the property's name.

OP_METHOD
---------

Adds a new method to a class.

OpCode: 0x21
Operands:
    - 0: The index of the constant hosting the method's name.

OP_INVOKE
---------

Optimized method invocation - immediately invoke a method after its name is accessed through its instance using the '.' operator.

OpCode: 0x22
Operands:
    - 0: The index of the constant hosting the method's name.
    - 1: The number of arguments to the method.

OP_INHERIT
----------

Make a superclass's methods and fields available to a subclass.

OpCode: 0x23
Operands: None

OP_GET_SUPER
----------

Get a member defined in a superclass

OpCode: 0x24
Operands: The index of the constant hosting the name of the superclass's member.

OP_INVOKE
---------

Optimized superclass method invocation - immediately invoke a method after its name is accessed through its instance using the '.' operator.

OpCode: 0x25
Operands:
    - 0: The index of the constant hosting the method's name.
    - 1: The number of arguments to the method.
