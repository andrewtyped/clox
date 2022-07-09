#!/usr/bin/env bash


SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

SRC_FILE="$SCRIPT_DIR/src/main.c"
SRC_DIR="$SCRIPT_DIR/src"
BIN_DIR="$SCRIPT_DIR/bin"
OBJ_DIR="$SCRIPT_DIR/obj"
OUT_FILE="$BIN_DIR/clox"

mkdir -p $BIN_DIR
mkdir -p $OBJ_DIR

FILES=("memory" \
       "chunk" \
       "main")

for f in ${FILES[@]}; do
    gcc -c "$SRC_DIR/$f.c" -o "$OBJ_DIR/$f.o" 
done

OBJFILES=$(for f in ${FILES[@]}; do echo "$OBJ_DIR/$f.o"; done)

echo $OBJFILES

gcc $OBJFILES -o $OUT_FILE