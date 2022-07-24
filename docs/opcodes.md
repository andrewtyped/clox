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