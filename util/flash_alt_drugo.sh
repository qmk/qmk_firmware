#! /bin/bash

# Steps to build and flash:
# source .venv/bin/activate
# qmk compile [-kb keyboard] [-km keymap] (NOTE: this script will always flash the massdrop/alt:drugo keymap)
# util/flash_alt_drugo.sh

echo "[*] Flashing massdrop_alt_drugo.bin..."
$HOME/qmk_firmware/util/mdloader_linux --first --download $HOME/qmk_firmare/massdrop_alt_drugo.bin --restart
