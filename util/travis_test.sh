#!/bin/bash

TRAVIS_COMMIT_MESSAGE="${TRAVIS_COMMIT_MESSAGE:-none}"
TRAVIS_COMMIT_RANGE="${TRAVIS_COMMIT_RANGE:-HEAD~1..HEAD}"

# test force push
#TRAVIS_COMMIT_RANGE="c287f1bfc5c8...81f62atc4c1d"

NUM_IMPACTING_CHANGES=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE} | grep -Ecv '^(docs/)')
BRANCH=$(git rev-parse --abbrev-ref HEAD)

if [[ "$TRAVIS_COMMIT_MESSAGE" == *"[skip test]"* ]]; then
    echo "Skipping due to commit message"
    exit 0
fi

if [ "$BRANCH" != "master" ] && [ "$NUM_IMPACTING_CHANGES" == "0" ]; then
    echo "Skipping due to changes not impacting tests"
    exit 0
fi

# if docker is installed - call make within the qmk docker image
if command -v docker >/dev/null; then
  function make() {
    docker run --rm -e MAKEFLAGS="$MAKEFLAGS" -w /qmk_firmware/ -v "$PWD":/qmk_firmware --user $(id -u):$(id -g) qmkfm/qmk_firmware make "$@"
  }
fi

make test:all
