#!/bin/bash

# Use Emscripten compiler instead of g++
CC=emcc

# Emscripten-specific flags.
CFLAGS="-s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 -s DEMANGLE_SUPPORT=1"
LDFLAGS="-s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s EXPORTED_RUNTIME_METHODS=[\"cwrap\",\"ccall\"] -s EXTRA_EXPORTED_RUNTIME_METHODS=[\"FS\"] --emrun"

# Include directory for header files
INCLUDE_DIR="-I./include"

# Create build directory if it doesn't exist
mkdir -p build

# Compile the source files into a WebAssembly module with HTML output
$CC $INCLUDE_DIR ./src/main.cpp ./src/setup.cpp ./src/controls.cpp ./src/buffering.cpp ./src/file_handling.cpp ./src/cleaning.cpp ./common/loadShader.cpp $CFLAGS $LDFLAGS -o ./build/progr.html
