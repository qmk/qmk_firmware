#!/bin/bash

# if docker is installed - call make within the qmk docker image
if command -v docker >/dev/null; then
  function make() {
    docker run --rm -e MAKEFLAGS="$MAKEFLAGS" -w /qmk_firmware/ -v "$PWD":/qmk_firmware --user $(id -u):$(id -g) qmkfm/base_container make "$@"
  }
fi

# test force push
#TRAVIS_COMMIT_RANGE="c287f1bfc5c8...81f62atc4c1d"

TRAVIS_COMMIT_MESSAGE="${TRAVIS_COMMIT_MESSAGE:-none}"
TRAVIS_COMMIT_RANGE="${TRAVIS_COMMIT_RANGE:-HEAD~1..HEAD}"
MAKE_ALL="make all:all"

if [[ "$TRAVIS_COMMIT_MESSAGE" != *"[skip build]"* ]] ; then
	exit_code=0
  echo "Making all keymaps for all of the ZSA keyboards"
  eval $MAKE_ALL
  : $((exit_code = $exit_code + $?))
	exit $exit_code
fi
