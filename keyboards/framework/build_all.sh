set -e
qmk compile -kb framework/ansi -km default
qmk compile -kb framework/iso -km default
qmk compile -kb framework/jis -km default
qmk compile -kb framework/numpad -km default
qmk compile -kb framework/macropad -km default
