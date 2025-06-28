#!/bin/bash

set -e
SILENT=true

TAG=${1:-$(git describe --tags --abbrev=0)}

# log which keyboard and keymap is compiled
function log_info() {
    echo "Compiled keyboard:$1 with keymap:$2"
}

for KEYMAP in "via" "default" "ryodeushii"; do
    for LAYOUT in "ansi" "iso"; do
        for KEYBOARD in "air75v2" "halo75v2" "halo96v2" "gem80"; do
            if [ ! -d "keyboards/nuphy/$KEYBOARD/$LAYOUT/keymaps/$KEYMAP" ] ; then
                continue
            fi
            CONFIG_H="keyboards/nuphy/$KEYBOARD/config.h"
            if [ ! -f $CONFIG_H ]; then
                CONFIG_H="keyboards/nuphy/$KEYBOARD/$LAYOUT/config.h"
            fi
            sed -i 's/put_version_here/'$TAG'/' $CONFIG_H
            if [ $KEYBOARD == "gem80" ]; then
                sed -i 's/WORK_MODE THREE_MODE/WORK_MODE USB_MODE/' $CONFIG_H

                qmk compile -kb nuphy/$KEYBOARD/$LAYOUT -km $KEYMAP -j 0 -c -e TARGET="wired-$KEYBOARD-$LAYOUT-$KEYMAP-$TAG" -e SILENT=$SILENT && log_info $KEYBOARD $KEYMAP

                sed -i 's/WORK_MODE USB_MODE/WORK_MODE THREE_MODE/' $CONFIG_H

                qmk compile -kb nuphy/$KEYBOARD/$LAYOUT -km $KEYMAP -j 0 -c -e TARGET="threemode-$KEYBOARD-$LAYOUT-$KEYMAP-$TAG" -e SILENT=$SILENT && log_info $KEYBOARD $KEYMAP
            else
                qmk compile --compiledb -e TARGET="$KEYBOARD-$LAYOUT-$KEYMAP-$TAG" -kb nuphy/$KEYBOARD/$LAYOUT -km $KEYMAP -j 0 -c -e SILENT=$SILENT && log_info $KEYBOARD $KEYMAP
            fi
            sed -i 's/'$TAG'/put_version_here/' $CONFIG_H
        done
    done
done
