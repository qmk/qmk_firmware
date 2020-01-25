#!/usr/bin/env bash
# This script requires that you have docker installed.
# To use it just provide the keyboard name as the first argument and the keymap as the second argument.
# The docker container is deleted after the compilation, so this does not leave any trace.
KEYBOARD=${1:-ergodox_ez}
KEYMAP=${2:-default}
docker run --rm -v $(pwd):/qmk_firmware -e keyboard="$KEYBOARD" -e subproject=" " -e keymap="$KEYMAP" qmk:latest make $KEYBOARD:$KEYMAP
