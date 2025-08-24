#!/bin/bash

COMMAND=${1:-build}
CONFIG=${2:-Release}
BUILD_DIR="build"
BIN_DIR="$BUILD_DIR/bin/$(uname -s | tr '[:upper:]' '[:lower:]')"
SANDBOX_EXE="$BIN_DIR/Sandbox"

function build() {
    mkdir -p "$BUILD_DIR"
    cmake -S . -B "$BUILD_DIR" -G Ninja -DCMAKE_BUILD_TYPE="$CONFIG" \
          -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
    cmake --build "$BUILD_DIR"
}

function run() {
    if [[ ! -f "$SANDBOX_EXE" ]]; then
        echo "⚠ Sandbox executable not found. Build first."
        exit 1
    fi
    "$SANDBOX_EXE"
}

function clean() {
    rm -rf "$BUILD_DIR"
    echo "Cleaned build directory."
}

case "$COMMAND" in
    build) build ;;
    run) run ;;
    rebuild) clean; build ;;
    clean) clean ;;
    *) echo "Unknown command. Usage: $0 build|run|rebuild|clean" ;;
esac