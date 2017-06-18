#!/bin/bash

TRAVIS_COMMIT_MESSAGE="${TRAVIS_COMMIT_MESSAGE:-none}"
TRAVIS_COMMIT_RANGE="${TRAVIS_COMMIT_RANGE:-HEAD~1..HEAD}"

if [[ "$TRAVIS_COMMIT_MESSAGE" != *"[skip build]"* ]] ; then 
	exit_code=0
	NEFM=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE} | grep -Ev '^(keyboards/)'  | grep -Ev '^(docs/)' | wc -l)
	BRANCH=$(git rev-parse --abbrev-ref HEAD)
	if [ $NEFM -gt 0 -o "$BRANCH" = "master" ]; then
		echo "Making all keymaps for all keyboards"
		make all-keyboards AUTOGEN="true"
		: $((exit_code = $exit_code + $?))
	else
		MKB=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE} | grep -oP '(?<=keyboards\/)([a-zA-Z0-9_]+)(?=\/)' | sort -u)
		for KB in $MKB ; do
			KEYMAP_ONLY=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE} | grep -Ev '^(keyboards/'${KB}'/keymaps/)' | wc -l)
			if [[ $KEYMAP_ONLY -gt 0 ]]; then
				echo "Making all keymaps for $KB"
				make ${KB}-allsp-allkm AUTOGEN=true
				: $((exit_code = $exit_code + $?))
			else
				MKM=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE} | grep -oP '(?<=keyboards/'${KB}'/keymaps/)([a-zA-Z0-9_]+)(?=\/)' | sort -u)
				for KM in $MKM ; do
					echo "Making $KM for $KB"	
					make ${KB}-allsp-${KM} AUTOGEN=true
					: $((exit_code = $exit_code + $?))
				done		
			fi
		done
	fi
	exit $exit_code
fi
