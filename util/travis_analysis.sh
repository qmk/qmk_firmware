#!/bin/bash

TRAVIS_COMMIT_MESSAGE="${TRAVIS_COMMIT_MESSAGE:-none}"
TRAVIS_COMMIT_RANGE="${TRAVIS_COMMIT_RANGE:-HEAD~1..HEAD}"

# test force push
#TRAVIS_COMMIT_RANGE="c287f1bfc5c8...81f62atc4c1d"

CHANGED_FILES=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE})
BRANCH=$(git rev-parse --abbrev-ref HEAD)

if [[ "$TRAVIS_COMMIT_MESSAGE" == *"[skip lint]"* ]]; then
    echo "Skipping due to commit message"
    exit 0
fi

# Lint markdown - output is only warnings till code base is up to scratch
echo "Linting markdown..."
markdownlint **/*.md --ignore='tmk_core/*' | true

# Maybe some C static analysis too???
