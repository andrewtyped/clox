#!/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

BUILD_DIR="$SCRIPT_DIR/build"

pushd $BUILD_DIR

ctest --verbose

popd