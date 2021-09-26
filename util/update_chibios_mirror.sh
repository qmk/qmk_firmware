#!/bin/bash

################################
# Configuration

# The ChibiOS branches to mirror
chibios_branches="trunk stable_20.3.x stable_21.6.x"

# The ChibiOS tags to mirror
chibios_tags="ver20.3.1 ver20.3.2 ver20.3.3 ver21.6.0"

# The ChibiOS-Contrib branches to mirror
contrib_branches="chibios-20.3.x"

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
    git svn init --stdlayout --prefix='svn/' http://svn.osdn.net/svnroot/chibios/
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

echo "Fetching latest from subversion..."
git svn fetch

echo "Updating ChibiOS branches..."
for branch in $chibios_branches ; do
    echo "Creating branch 'svn-mirror/$branch' from 'svn/$branch'..."
    git branch -f svn-mirror/$branch svn/$branch \
        && git push qmk svn-mirror/$branch
done

echo "Updating ChibiOS tags..."
for tagname in $chibios_tags ; do
    echo "Creating tag 'svn-mirror/$tagname' from 'svn/tags/$tagname'..."
    GIT_COMMITTER_DATE="$(git log -n1 --pretty=format:'%ad' svn/tags/$tagname)" git tag -f -a -m "Tagging $tagname" svn-mirror/$tagname svn/tags/$tagname
    git push qmk svn-mirror/$tagname
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
        && git push qmk mirror/$branch
done
