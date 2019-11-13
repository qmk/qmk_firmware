#!/bin/bash

# Git Setup
echo -e "TRAVIS_REPO_SLUG = $TRAVIS_REPO_SLUG"
echo -e "TRAVIS_BRANCH = $TRAVIS_BRANCH"
echo -e "CURRENT COMMIT HASH = $(git rev-parse --short HEAD)"
echo -e "CURRENT BRANCH = $(git rev-parse --abbrev-ref HEAD)"

# Add QMK repository as `upstream`
echo -e "\nAdding the QMK repository as remote \"upstream\"..."
git remote add upstream https://github.com/qmk/qmk_firmware.git

# Fetch the branch being targeted by the pull request (The "base" branch)
echo -e "\nFetching refs for qmk:master..."
git fetch upstream master
CURRENT_MASTER=$(git log -n 1 --pretty=format:"%H" upstream/master)
echo -e "\nThe current SHA of qmk:master is \e[32m$CURRENT_MASTER\e[0m"
UNMERGED_COMMITS=$(git rev-list --left-right $CURRENT_MASTER...$(git rev-parse --short HEAD) | grep -E '^>' | wc -l)

# How many commits are exclusive to the "base" branch $CURRENT_MASTER
# and to the "head" branch $TRAVIS_PULL_REQUEST_SHA
echo -e "The current branch contains $(git diff --name-only HEAD~$UNMERGED_COMMITS HEAD | wc -l) edited file(s) from $UNMERGED_COMMITS unmerged commit(s)."

echo -e "\nEdited files:"
git diff --name-only HEAD~$UNMERGED_COMMITS HEAD

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
