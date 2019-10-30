#!/bin/bash

# if docker is installed - patch calls to within the qmk docker image
if command -v docker >/dev/null; then
    function make() {
        docker run --rm -e MAKEFLAGS="$MAKEFLAGS" -w /qmk_firmware/ -v "$PWD":/qmk_firmware --user $(id -u):$(id -g) qmkfm/base_container make "$@"
    }
    function qmk() {
        docker run --rm -w /qmk_firmware/ -v "$PWD":/qmk_firmware --user $(id -u):$(id -g) qmkfm/base_container bin/qmk "$@"
    }
fi

TRAVIS_COMMIT_MESSAGE="${TRAVIS_COMMIT_MESSAGE:-none}"
TRAVIS_COMMIT_RANGE="${TRAVIS_COMMIT_RANGE:-HEAD~1..HEAD}"

# test force push
#TRAVIS_COMMIT_RANGE="c287f1bfc5c8...81f62atc4c1d"

BRANCH=$(git rev-parse --abbrev-ref HEAD)
CHANGES=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE})

NUM_CORE_CHANGES=$(echo "$CHANGES" | grep -Ecv -e '^(docs/)' -e '^(keyboards/)' -e '^(layouts/)')
NUM_PY_CHANGES=$(echo "$CHANGES" | grep -Ec -e '^(lib/python/)' -e '^(bin/qmk)')

if [[ "$TRAVIS_COMMIT_MESSAGE" == *"[skip test]"* ]]; then
    echo "Skipping due to commit message"
    exit 0
fi

exit_code=0

if [ "$BRANCH" == "master" ] || [ "$NUM_CORE_CHANGES" != "0" ]; then
    echo "Running tests."
    make test:all
    : $((exit_code = $exit_code + $?))

fi

if [ "$BRANCH" == "master" ] || [ "$NUM_PY_CHANGES" != "0" ]; then
    echo "Running python tests."
    qmk pytest
    : $((exit_code = $exit_code + $?))
fi

exit $exit_code
