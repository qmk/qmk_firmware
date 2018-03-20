#!/bin/bash

TRAVIS_COMMIT_MESSAGE="${TRAVIS_COMMIT_MESSAGE:-none}"
TRAVIS_COMMIT_RANGE="${TRAVIS_COMMIT_RANGE:-HEAD~1..HEAD}"

if [[ "$TRAVIS_COMMIT_MESSAGE" != *"[skip docs]"* ]] ; then 
	if git diff --name-only ${TRAVIS_COMMIT_RANGE} | grep -e '^quantum/' -e '^tmk_core/' -e '^docs/api_.*'; then
		echo "Generating API docs..."
		rm -rf doxygen
		doxygen Doxyfile
		moxygen -a -g -o docs/api_%s.md doxygen/xml
	fi
fi
