#!/bin/bash

set -e
SILENT=true

TAG=${1:-$(git describe --tags --abbrev=0)}

# log which keyboard and keymap is compiled
function log_info() {
    echo "Compiled keyboard:$1 with keymap:$2"
}

for KEYMAP in "via" "default" "ryodeushii"; do
    for KEYBOARD in "air75v2" "halo75v2" "gem80"; do
        sed -i 's/put_version_here/'$TAG'/' keyboards/nuphy/$KEYBOARD/ansi/config.h
        if [ $KEYBOARD == "gem80" ]; then
            sed -i 's/WORK_MODE THREE_MODE/WORK_MODE USB_MODE/' keyboards/nuphy/gem80/ansi/config.h

            qmk compile -kb nuphy/$KEYBOARD/ansi -km $KEYMAP -j 0 -c -e TARGET="wired-$KEYBOARD-$KEYMAP-$TAG" -e SILENT=$SILENT && log_info $KEYBOARD $KEYMAP

            sed -i 's/WORK_MODE USB_MODE/WORK_MODE THREE_MODE/' keyboards/nuphy/gem80/ansi/config.h

            qmk compile -kb nuphy/$KEYBOARD/ansi -km $KEYMAP -j 0 -c -e TARGET="threemode-$KEYBOARD-$KEYMAP-$TAG" -e SILENT=$SILENT && log_info $KEYBOARD $KEYMAP
        else
            qmk compile --compiledb -e TARGET="$KEYBOARD-$KEYMAP-$TAG" -kb nuphy/$KEYBOARD/ansi -km $KEYMAP -j 0 -c -e SILENT=$SILENT && log_info $KEYBOARD $KEYMAP
        fi
        sed -i 's/'$TAG'/put_version_here/' keyboards/nuphy/$KEYBOARD/ansi/config.h
    done
done
