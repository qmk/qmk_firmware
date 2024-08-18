#!/bin/bash

set -e

TAG=${1:-$(git describe --tags --abbrev=0)}

# log which keyboard and keymap is compiled
function log_info() {
    echo "Compiled keyboard:$1 with keymap:$2"
}

for KEYMAP in "via" "default" "ryodeushii"
do
    for KEYBOARD in "air75v2" "halo75v2" "gem80"
    do
        if [ $KEYBOARD == "gem80" ]; then
            sed -i 's/WORK_MODE THREE_MODE/WORK_MODE USB_MODE/' keyboards/nuphy/gem80/ansi/config.h

            qmk compile -kb nuphy/$KEYBOARD/ansi -km $KEYMAP -j 0 -c -e TARGET="wired-$KEYBOARD-$KEYMAP-$TAG"  > /dev/null && log_info $KEYBOARD $KEYMAP

            sed -i 's/WORK_MODE USB_MODE/WORK_MODE THREE_MODE/' keyboards/nuphy/gem80/ansi/config.h

            qmk compile -kb nuphy/$KEYBOARD/ansi -km $KEYMAP -j 0 -c -e TARGET="threemode-$KEYBOARD-$KEYMAP-$TAG"  > /dev/null && log_info $KEYBOARD $KEYMAP
        else
            qmk compile --compiledb -e TARGET="$KEYBOARD-$KEYMAP-$TAG" -kb nuphy/$KEYBOARD/ansi -km $KEYMAP -j 0 -c  > /dev/null && log_info $KEYBOARD $KEYMAP
        fi
    done
done
