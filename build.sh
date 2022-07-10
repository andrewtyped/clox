#!/usr/bin/env bash


SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

SRC_FILE="$SCRIPT_DIR/src/main.c"
SRC_DIR="$SCRIPT_DIR/src"
BUILD_DIR="$SCRIPT_DIR/build"
OBJ_DIR="$SCRIPT_DIR/obj"
OUT_FILE="$BIN_DIR/clox"

mkdir -p $BUILD_DIR

cmake -S "$SCRIPT_DIR" -B $BUILD_DIR
cmake --build "$BUILD_DIR"