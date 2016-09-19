#!/bin/bash

set -o errexit -o nounset

rev=$(git rev-parse --short HEAD)

git config --global user.name "Travis CI"
git config --global user.email "jack.humb+travis.ci@gmail.com"

make ergodox-ez AUTOGEN=true

find . -name ".build" | xargs rm -rf
cd ..
git clone https://$GH_TOKEN@github.com/jackhumbert/qmk.fm.git
cd qmk.fm
git submodule update --init --recursive
rm -rf keyboard
rm -rf keyboards
cp -r ../qmk_firmware/keyboards .
mkdir keyboards/ergodox_ez/
cp ../qmk_firmware/util/ergodox_ez.html keyboards/ergodox_ez/index.html
cp ../qmk_firmware/readme.md qmk_readme.md
./generate.sh

git add -A
git commit -m "generated from qmk_firmware/$TRAVIS_BRANCH@${rev}" 
git push
