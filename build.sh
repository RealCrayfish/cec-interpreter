#!/bin/sh
g++ -Iinclude -Llib -Wall -Wextra -pedantic -g -fdiagnostics-color=always -O2 -Llib src/main.cpp -o build/debug/cec 