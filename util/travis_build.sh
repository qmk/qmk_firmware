#!/bin/bash

TRAVIS_COMMIT_MESSAGE="${TRAVIS_COMMIT_MESSAGE:-none}"
TRAVIS_COMMIT_RANGE="${TRAVIS_COMMIT_RANGE:-HEAD~1..HEAD}"

if [[ "$TRAVIS_COMMIT_MESSAGE" != *"[skip build]"* ]] ; then 
	NEFM=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE} | grep -Ev '^(keyboards/)' | wc -l)
	if [[ $NEFM -gt 0 ]] ; then
		echo "Making all keymaps for all keyboards"
		make all-keyboards AUTOGEN="true"
	else
		MKB=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE} | grep -oP '(?<=keyboards\/)([a-zA-Z_]+)' | sort -u)
		for KB in $MKB ; do
			echo "Making all keymaps for $KB"
			make "$KB" AUTOGEN="true"
		done
	fi
fi
