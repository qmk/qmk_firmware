#!/usr/bin/env bash

source util/travis_utils.sh

if [[ "$TRAVIS_COMMIT_MESSAGE" == *"[skip test]"* ]]; then
    echo "Skipping due to commit message"
    exit 0
fi

exit_code=0

if [ "$LOCAL_BRANCH" == "master" ] || [ "$NUM_CORE_CHANGES" != "0" ]; then
    echo "Running tests."
    make test:all
    : $((exit_code = $exit_code + $?))

fi

exit $exit_code
