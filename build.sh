#!/bin/bash
mkdir -p bin/
rm bin/*
gcc src/*.c -o bin/emu -std=c99