#!/bin/bash

source util/travis_utils.sh

# Git Setup
echo -e "TRAVIS_REPO_SLUG = $TRAVIS_REPO_SLUG"
echo -e "LOCAL_BRANCH = ${TRAVIS_PULL_REQUEST_BRANCH:-${TRAVIS_BRANCH}}"
#disabled because it's null at this point
#echo -e "QMK_CHANGES = ${QMK_CHANGES}"
echo -e "TRAVIS_BRANCH = $TRAVIS_BRANCH"
echo -e "TRAVIS_COMMIT_RANGE = $TRAVIS_COMMIT_RANGE"
CURRENT_COMMIT_HASH=$(git rev-parse --short HEAD)
echo -e "CURRENT_COMMIT_HASH = $(git rev-parse --short HEAD)"
echo -e "CURRENT BRANCH = $(git rev-parse --abbrev-ref HEAD)"
echo -e "------------------------------------------------------------"

# Add QMK repository as `upstream`
echo -e "\nAdding the QMK repository as remote \"upstream\"..."
git remote add upstream https://github.com/qmk/qmk_firmware.git

# Fetch the branch being targeted by the pull request (The "base"
# branch)
echo -e "\nFetching refs for qmk:master..."
git fetch upstream master

# The SHA of qmk:master
CURRENT_MASTER=$(git log -n 1 --pretty=format:"%H" upstream/master)
echo -e "\nThe current SHA of qmk:master is \e[32m$CURRENT_MASTER\e[0m"

# The latest common ancestor of qmk:master and our development branch
BRANCH_BASE=$(git merge-base ${CURRENT_MASTER} ${TRAVIS_BRANCH})
echo -e "\nThe latest common ancestor of qmk:master and this branch is \e[32m$BRANCH_BASE\e[0m"

# The number of commits to the development branch that are not merged
# into qmk:master
UNMERGED_COMMITS=$(git rev-list --left-right $BRANCH_BASE...$(git rev-parse --short HEAD) | grep -E '^>' | wc -l)

# Branch summary
echo -e "The current branch contains $(git diff --name-only $BRANCH_BASE HEAD | wc -l) edited file(s) from $UNMERGED_COMMITS unmerged commit(s)."

# List the files edited by this branch
echo -e "\nEdited files:"
FILES_EDITED=$(git diff --name-only ${BRANCH_BASE}...${CURRENT_COMMIT_HASH})
echo -e "$FILES_EDITED"
echo

NUM_CORE_CHANGES=$(echo "$FILES_EDITED" | grep -Ecv -e '^(docs/)' -e '^(keyboards/)' -e '^(layouts/)' -e '^(util/)' -e '^(lib/python/)' -e '^(bin/qmk)' -e '^(requirements.txt)' -e '(.travis.yml)')
echo -e "$NUM_CORE_CHANGES"
echo -e "$FILES_EDITED | grep -Ev -e '^(docs/)' -e '^(keyboards/)' -e '^(layouts/)' -e '^(util/)' -e '^(lib/python/)' -e '^(bin/qmk)' -e '^(requirements.txt)' -e '(.travis.yml)')"

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
