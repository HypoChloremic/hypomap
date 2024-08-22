#!/bin/bash

CC=emcc
CFLAGS="`pkg-config --cflags glew glfw3`"
LDFLAGS="`pkg-config --libs glew glfw3` -lglut -Wall"

# Include directory for header files
INCLUDE_DIR="-I./include"

mkdir -p build

$CC $INCLUDE_DIR ./src/main.cpp ./src/setup.cpp ./src/controls.cpp ./src/buffering.cpp ./src/file_handling.cpp ./src/cleaning.cpp ./common/loadShader.cpp $CFLAGS $LDFLAGS -o ./build/progr.html -s USE_GLFW=3 -s FULL_ES2=1 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s ASSERTIONS=1 --preload-file shaders
