#!/bin/bash

# Git Setup
echo -e "TRAVIS_REPO_SLUG = $TRAVIS_REPO_SLUG"
echo -e "TRAVIS_BRANCH = $TRAVIS_BRANCH"
echo -e "CURRENT COMMIT HASH = $(git rev-parse --short HEAD)"
echo -e "CURRENT BRANCH = $(git rev-parse --abbrev-ref HEAD)"

# Add QMK repository as `upstream`
echo -e "\nAdd QMK repository as \`upstream\`..."
git remote add upstream https://github.com/qmk/qmk_firmware.git

# Confirm the remote was added
echo -e "\nRemote repositories:"
git remote -v

# Fetch the branch being targeted by the pull request (The "base" branch)
echo -e "\nFetching refs for qmk:master..."
git fetch upstream master
CURRENT_MASTER=$(git log -n 1 --pretty=format:"%H" upstream/master)
echo -e "\nCurrent SHA of qmk:master is $CURRENT_MASTER"

# How many commits are exclusive to the "base" branch $CURRENT_MASTER
# and to the "head" branch $TRAVIS_PULL_REQUEST_SHA
git rev-list --left-right --count $CURRENT_MASTER...$TRAVIS_PULL_REQUEST_SHA

# If $TRAVIS_PULL_REQUEST is not false, then the build was triggered by
# a pull request. Otherwise, the build was triggered by a push.
if [ "$TRAVIS_PULL_REQUEST" != "false" ]
then
	# Triggered by pull request
	echo "This is a pull request."
	# How many commits are exclusive to the "base" branch
	# $CURRENT_MASTER and to the "head" branch
	#git rev-list --left-right --count $TRAVIS_BRANCH...$TRAVIS_PULL_REQUEST_SHA
else
	echo "This is not a pull request."
fi

# echo -e $TRAVIS_REPO_SLUG / $TRAVIS_BRANCH
