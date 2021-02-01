# Use this by sourcing it in your script.

# Provide sane defaults for travis environment
TRAVIS_BRANCH="${TRAVIS_BRANCH:master}"
TRAVIS_PULL_REQUEST="${TRAVIS_PULL_REQUEST:false}"
TRAVIS_COMMIT_MESSAGE="${TRAVIS_COMMIT_MESSAGE:-none}"
TRAVIS_COMMIT_RANGE="${TRAVIS_COMMIT_RANGE:-HEAD~1..HEAD}"

# test force push
#TRAVIS_COMMIT_RANGE="c287f1bfc5c8...81f62atc4c1d"

# Extra variables
LOCAL_BRANCH=$(git rev-parse --abbrev-ref HEAD)
QMK_CHANGES=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE})
NUM_CORE_CHANGES=$(echo "$QMK_CHANGES" | grep -Ec -e '^Makefile' -e '^[^/]*.mk' -e '^drivers/' -e '^lib/atsam' -e '^lib/lib8tion/' -e '^platforms' -e '^quantum' -e '^tests' -e '^tmk_core')

# if docker is installed - patch calls to within the qmk docker image
if command -v docker >/dev/null; then
    function make() {
        docker run --rm -e MAKEFLAGS="$MAKEFLAGS" -w /qmk_firmware/ -v "$PWD":/qmk_firmware --user $(id -u):$(id -g) qmkfm/base_container make "$@"
    }
    function qmk() {
        docker run --rm -w /qmk_firmware/ -v "$PWD":/qmk_firmware --user $(id -u):$(id -g) qmkfm/base_container bin/qmk "$@"
    }
fi
