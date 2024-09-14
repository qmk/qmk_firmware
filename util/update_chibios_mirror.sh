#!/bin/bash

################################
# Configuration

# The ChibiOS branches to mirror
chibios_branches="trunk stable_21.11.x"

# The ChibiOS-Contrib branches to mirror
contrib_branches="chibios-21.11.x"

################################
# Actions

set -eEuo pipefail
umask 022

this_script="$(realpath "${BASH_SOURCE[0]}")"
script_dir="$(realpath "$(dirname "$this_script")")"
qmk_firmware_dir="$(realpath "$script_dir/../")"
chibios_dir="$qmk_firmware_dir/lib/chibios"
contrib_dir="$qmk_firmware_dir/lib/chibios-contrib"

chibios_git_location=$(realpath "$chibios_dir/$(cat "$chibios_dir/.git" | awk '/gitdir:/ {print $2}')")
chibios_git_config=$(realpath "$chibios_git_location/config")
contrib_git_location=$(realpath "$contrib_dir/$(cat "$contrib_dir/.git" | awk '/gitdir:/ {print $2}')")
contrib_git_config=$(realpath "$contrib_git_location/config")

cd "$chibios_dir"

if [[ -z "$(cat "$chibios_git_config" | grep '\[svn-remote "svn"\]')" ]] ; then
    git svn init --stdlayout --prefix='svn/' https://svn.code.sf.net/p/chibios/code/
fi

if [[ -z "$(cat "$chibios_git_config" | grep '\[remote "qmk"\]')" ]] ; then
    git remote add qmk git@github.com:qmk/ChibiOS.git
    git remote set-url qmk git@github.com:qmk/ChibiOS.git --push
else
    git remote set-url qmk git@github.com:qmk/ChibiOS.git
    git remote set-url qmk git@github.com:qmk/ChibiOS.git --push
fi

echo "Updating remotes..."
git fetch --all --tags --prune

echo "Ensure refs actually match up..."
for branch in $chibios_branches ; do
    echo "Matching $branch..."
    git update-ref refs/remotes/svn/$branch refs/remotes/qmk/svn-mirror/$branch
done

echo "Fetching latest from subversion..."
git svn fetch

echo "Updating ChibiOS branches..."
for branch in $chibios_branches ; do
    echo "Creating branch 'svn-mirror/$branch' from 'svn/$branch'..."
    git branch -f svn-mirror/$branch svn/$branch \
        && git push qmk svn-mirror/$branch
done

cd "$contrib_dir"

if [[ -z "$(cat "$contrib_git_config" | grep '\[remote "qmk"\]')" ]] ; then
    git remote add qmk git@github.com:qmk/ChibiOS-Contrib.git
    git remote set-url qmk git@github.com:qmk/ChibiOS-Contrib.git --push
else
    git remote set-url qmk git@github.com:qmk/ChibiOS-Contrib.git
    git remote set-url qmk git@github.com:qmk/ChibiOS-Contrib.git --push
fi

if [[ -z "$(cat "$contrib_git_config" | grep '\[remote "upstream"\]')" ]] ; then
    git remote add upstream git@github.com:ChibiOS/ChibiOS-Contrib.git
    git remote set-url upstream git@github.com:ChibiOS/ChibiOS-Contrib.git --push
else
    git remote set-url upstream git@github.com:ChibiOS/ChibiOS-Contrib.git
    git remote set-url upstream git@github.com:ChibiOS/ChibiOS-Contrib.git --push
fi

echo "Updating remotes..."
git fetch --all --tags --prune

echo "Updating ChibiOS-Contrib branches..."
for branch in $contrib_branches ; do
    echo "Creating branch 'mirror/$branch' from 'upstream/$branch'..."
    git branch -f mirror/$branch upstream/$branch \
        && git push qmk mirror/$branch || true # Allow for nonexistent ChibiOS-Contrib branches -- they'll turn up eventually.
done
