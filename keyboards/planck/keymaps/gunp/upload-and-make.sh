#!/usr/bin/env bash

pushd ~/git-repos/qmk_firmware/
rm -rf keyboards/planck/keymaps/gunp/
cp -rf ~/git-repos/gunp-geek-repo/qmk-planck/ keyboards/planck/keymaps/gunp/
if [[ $2 == "dfu" ]]; then
    # sudo dfu-programmer atmega32u4 erase --force
    # sudo dfu-programmer atmega32u4 flash .build/planck_rev4_gunp.hex
    # sudo dfu-programmer atmega32u4 reset
    sudo make planck/$1:gunp:dfu
    # bash ~/bin/gunp-kb-layout-reset
else
    make planck/$1:gunp:clean
    make planck/$1:gunp:all
fi
popd
