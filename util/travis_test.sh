#!/bin/bash

source util/travis_utils.sh

NUM_CORE_CHANGES=$(echo "$QMK_CHANGES" | grep -Ecv -e '^(docs/)' -e '^(keyboards/)' -e '^(layouts/)' -e '^(util/)' -e '^(lib/python/)' -e '^(bin/qmk)' -e '^(requirements.txt)' -e '(.travis.yml)')
NUM_PY_CHANGES=$(echo "$QMK_CHANGES" | grep -Ec -e '^(lib/python/)' -e '^(bin/qmk)')

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

if [ "$LOCAL_BRANCH" == "master" ] || [ "$NUM_PY_CHANGES" != "0" ]; then
    echo "Running python tests."
    qmk pytest
    : $((exit_code = $exit_code + $?))
fi

exit $exit_code
