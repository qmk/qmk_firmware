#!/bin/bash

# test force push
#TRAVIS_COMMIT_RANGE="c287f1bfc5c8...81f62atc4c1d"

TRAVIS_COMMIT_MESSAGE="${TRAVIS_COMMIT_MESSAGE:-none}"
TRAVIS_COMMIT_RANGE="${TRAVIS_COMMIT_RANGE:-HEAD~1..HEAD}"
MAKE_ALL="make all:default"

if [[ "$TRAVIS_COMMIT_MESSAGE" != *"[skip build]"* ]] ; then
	exit_code=0
	git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE}
	if [ $? -eq 128 ]; then
		echo "Making default keymaps for all keyboards"
		eval $MAKE_ALL
		: $((exit_code = $exit_code + $?))
	else
		NEFM=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE} | grep -Ev '^(keyboards/)'  | grep -Ev '^(docs/)' | wc -l)
		BRANCH=$(git rev-parse --abbrev-ref HEAD)
		if [ $NEFM -gt 0 -o "$BRANCH" = "master" ]; then
			echo "Making default keymaps for all keyboards"
			eval $MAKE_ALL
			: $((exit_code = $exit_code + $?))
		else
			MKB=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE} | grep -oP '(?<=keyboards\/)([a-zA-Z0-9_\/]+)(?=\/)' | sort -u)
			for KB in $MKB ; do
				if [[ $KB == *keymaps* ]]; then
					continue
				fi
				KEYMAP_ONLY=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE} | grep -Ev '^(keyboards/'${KB}'/keymaps/)' | wc -l)
				if [[ $KEYMAP_ONLY -gt 0 ]]; then
					echo "Making all keymaps for $KB"
					make ${KB}:all
					: $((exit_code = $exit_code + $?))
				else
					MKM=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE} | grep -oP '(?<=keyboards/'${KB}'/keymaps/)([a-zA-Z0-9_]+)(?=\/)' | sort -u)
					for KM in $MKM ; do
						echo "Making $KM for $KB"
						make ${KB}:${KM}
						: $((exit_code = $exit_code + $?))
					done
				fi
			done
		fi
	fi
	exit $exit_code
fi
