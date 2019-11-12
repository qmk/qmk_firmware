#!/bin/bash

# Git Setup
echo -e "\nTRAVIS_REPO_SLUG = $TRAVIS_REPO_SLUG\nTRAVIS_BRANCH = $TRAVIS_BRANCH"

# Add QMK repository as `upstream`
echo "$ git remote add upstream https://github.com/qmk/qmk_firmware.git"
git remote add upstream https://github.com/qmk/qmk_firmware.git

# Confirm the remote was added
echo "$ git remote -v"
git remote -v

# Fetch the branch being targeted by the pull request (The "base" branch)
echo "git fetch upstream $TRAVIS_BRANCH"
git fetch upstream $TRAVIS_BRANCH

# How many commits are exclusive to the "base" branch and to the "head" branch
git rev-list --left-right --count $TRAVIS_BRANCH...$TRAVIS_PULL_REQUEST_SHA

if [ "$TRAVIS_PULL_REQUEST" != "false" ]
then
	echo "This is a pull request."
else
	echo "This is not a pull request."
fi

echo -e $TRAVIS_REPO_SLUG / $TRAVIS_BRANCH
