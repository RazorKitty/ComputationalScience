#!/bin/env sh
rm -f output.txt noisy.csv && gcc -o exy main.c -lm && chmod +x exy && ./exy.exe && cat output.txt
