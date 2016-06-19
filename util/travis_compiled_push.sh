#!/bin/bash

set -o errexit -o nounset

rev=$(git rev-parse --short HEAD)

git config user.name "Travis CI"
git config user.email "jack.humb+travis.ci@gmail.com"
git remote rm origin
git remote add origin "https://$GH_TOKEN@github.com/jackhumbert/qmk_firmware.git"
git fetch origin
[[ $(git branch | grep $TRAVIS_BRANCH-automated-build) != "" ]] && git branch -D $TRAVIS_BRANCH-automated-build
git checkout -b $TRAVIS_BRANCH-automated-build
git commit -am "adds compiled files from $TRAVIS_BRANCH@${rev}" 
git push origin $TRAVIS_BRANCH-automated-build