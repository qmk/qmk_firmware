#!/bin/bash

set -o errexit -o nounset

# if [ "$TRAVIS_BRANCH" != "master" ]
# then
#   echo "This commit was made against the $TRAVIS_BRANCH and not the master! No deploy!"
#   exit 0
# fi

rev=$(git rev-parse --short HEAD)

git config user.name "Travis CI"
git config user.email "jack.humb+travis.ci@gmail.com"
git remote add origin "https://$GH_TOKEN@github.com/jackhumbert/qmk_firmware.git"

git commit --amend -C HEAD
git push origin/$TRAVIS_BRANCH