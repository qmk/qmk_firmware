#!/bin/bash

TRAVIS_COMMIT_MESSAGE="${TRAVIS_COMMIT_MESSAGE:-none}"
TRAVIS_COMMIT_RANGE="${TRAVIS_COMMIT_RANGE:-HEAD~1..HEAD}"

NUM_CORE_CHANGES=$(echo "$QMK_CHANGES" | grep -Ecv -e '^(docs/)' -e '^(keyboards/)' -e '^(layouts/)' -e '^(util/)' -e '^(lib/python/)' -e '^(bin/qmk)' -e '^(requirements.txt)' -e '(.travis.yml)')

if [[ "$TRAVIS_COMMIT_MESSAGE" == *"[skip test]"* ]]; then
    echo "Skipping due to commit message"
    exit 0
fi

if [ "$BRANCH" != "master" ] && [ "$NUM_IMPACTING_CHANGES" == "0" ]; then
    echo "Skipping due to changes not impacting tests"
    exit 0
fi

exit $exit_code
