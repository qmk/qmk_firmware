#!/usr/bin/env bash

# First, compile
make git-submodule
qmk compile -e CONVERT_TO=liatris -kb splitkb/kyria/rev3 -km my_kyria_layout

# Then, create keymap image
qmk c2json -kb splitkb/kyria/rev3 -km my_kyria_layout | poetry run keymap parse -c 10  -q - > .build/keymap.yaml
poetry run python fix_keymap_yaml.py ".build/keymap.yaml"
poetry run keymap draw .build/keymap.yaml > keymap.svg
