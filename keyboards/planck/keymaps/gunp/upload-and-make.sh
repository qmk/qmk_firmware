#!/usr/bin/env bash

pushd ~/git-repos/qmk_firmware/
rm -rf keyboards/planck/keymaps/gunp/
cp -rf ~/git-repos/gunp-geek-repo/qmk-planck/ keyboards/planck/keymaps/gunp/
if [[ $2 == "dfu" ]]; then
    sudo make planck/$1:gunp:dfu
else
    # make git-submodule
    make clean planck/$1:gunp
fi
popd
