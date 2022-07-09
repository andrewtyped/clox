#!/usr/bin/env bash


SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

SRC_FILE="$SCRIPT_DIR/src/main.c"
OUT_DIR="$SCRIPT_DIR/bin"
OUT_FILE="$OUT_DIR/clox"

mkdir -p $OUT_DIR


gcc $SRC_FILE -o $OUT_FILE