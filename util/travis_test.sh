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

make test:all
