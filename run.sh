#!/bin/env sh
gcc -o exy main.c -lm && chmod +x exy && ./exy && cat output.txt
