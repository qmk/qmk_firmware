#!/bin/bash

################################
# Configuration

# The branches to mirror
branches="trunk stable_20.3.x stable_21.6.x"

# The tags to mirror
tags="ver19.1.3 ver20.3.1 ver20.3.2 ver20.3.3 ver21.6.0"

################################
# Actions

set -eEuo pipefail
umask 022

this_script="$(realpath "${BASH_SOURCE[0]}")"
script_dir="$(realpath "$(dirname "$this_script")")"
qmk_firmware_dir="$(realpath "$script_dir/../")"
chibios_dir="$qmk_firmware_dir/lib/chibios"

chibios_git_location=$(realpath "$chibios_dir/$(cat "$chibios_dir/.git" | awk '/gitdir:/ {print $2}')")
chibios_git_config=$(realpath "$chibios_git_location/config")

cd "$chibios_dir"

if [[ -z "$(cat "$chibios_git_config" | grep '\[svn-remote "svn"\]')" ]] ; then
    git svn init --stdlayout --prefix='svn/' http://svn.osdn.net/svnroot/chibios/
fi

if [[ -z "$(cat "$chibios_git_config" | grep '\[remote "qmk"\]')" ]] ; then
    git remote add qmk git@github.com:qmk/ChibiOS.git
    git remote set-url qmk git@github.com:qmk/ChibiOS.git --push
fi

echo "Updating remotes..."
git fetch --all --tags --prune

echo "Fetching latest from subversion..."
git svn fetch

echo "Updating branches..."
for branch in $branches ; do
    echo "Creating branch 'svn-mirror/$branch' from 'svn/$branch'..."
    git branch -f svn-mirror/$branch svn/$branch \
        && git push qmk svn-mirror/$branch
done

echo "Updating tags..."
for tagname in $tags ; do
    echo "Creating tag 'svn-mirror/$tagname' from 'svn/tags/$tagname'..."
    GIT_COMMITTER_DATE="$(git log -n1 --pretty=format:'%ad' svn/tags/$tagname)" git tag -f -a -m "Tagging $tagname" svn-mirror/$tagname svn/tags/$tagname
    git push qmk svn-mirror/$tagname
done