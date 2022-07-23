clox Op Codes
==============

Each op code is one byte, and accepts 0 or more operands.

OP_CONSTANT
-----------

Loads a constant value from the current chunk.

OpCode: 00
Operands:
- 0: index of constant to load

OP_RETURN
---------

OpCode: 01
Operands: None