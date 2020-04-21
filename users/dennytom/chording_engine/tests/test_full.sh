#!/bin/sh
cd ..
python3 parser.py tests/test_keymap_def.json tests/test_keymap.c && \
gcc -g tests/test.c -o tests/test && \
tests/test && \
python3 parser.py ../../../keyboards/butterstick/keymaps/tomas/keymap_def.json ../../../keyboards/butterstick/keymaps/tomas/keymap.c && \
python3 parser.py ../../../keyboards/georgi/keymaps/tomas/keymap_def.json ../../../keyboards/georgi/keymaps/tomas/keymap.c && \
python3 parser.py ../../../keyboards/georgi/keymaps/buttery/keymap_def.json ../../../keyboards/georgi/keymaps/buttery/keymap.c && \
cd ../../../ && \
make butterstick && \
make georgi