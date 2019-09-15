#!/usr/bin/env bash

pushd ~/git-repos/qmk_firmware/

rm -rf keyboards/planck/keymaps/gunp/
cp -rf ~/git-repos/gunp-geek-repo/qmk-planck/ keyboards/planck/keymaps/gunp/
rm -rf keyboards/planck/keymaps/gunp/archive/
rm -f keyboards/planck/keymaps/gunp/gunp_planck.png
sed -i 's/gunp_planck.png/https:\/\/drive.google.com\/uc?export=view\&id='\
'1A2z7r_3bhXq0hS4O3yxaO-ZXeJBzlIqB'\
'/g' keyboards/planck/keymaps/gunp/readme.md

if [[ $2 == "dfu" ]]; then
    sudo make planck/$1:gunp:dfu
else
    # make git-submodule
    make clean planck/$1:gunp
fi

popd
