#!/bin/sh

cd ..
python3 parser.py tests/test_keymap_def.json tests/test_keymap.c && \
gcc -g tests/test.c -o tests/test && \
tests/test