#!/bin/bash

set -o errexit -o nounset

rev=$(git rev-parse --short HEAD)

git config --global user.name "Travis CI"
git config --global user.email "jack.humb+travis.ci@gmail.com"

find . -name ".build" | xargs rm -rf
cd ..
git clone https://$GH_TOKEN@github.com/jackhumbert/qmk.fm.git
cd qmk.fm
rm -rf keyboard
cp -r ../qmk_firmware/keyboard .
./generate.sh

git add -A
git commit -m "complete keyboards and compiled files from qmk_firmware/$TRAVIS_BRANCH@${rev}" 
git push