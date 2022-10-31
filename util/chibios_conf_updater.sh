#!/usr/bin/env bash

set -eEuo pipefail
umask 022

#####################
# You will need to get an older JDK -- JDK 8
#
# !!!!!!!! DO NOT INSTALL THIS IF YOU HAVE AN EXISTING JDK OR JRE INSTALLED !!!!!!!!
#
# For Debian 10-ish distro's:
#   wget -qO - https://adoptopenjdk.jfrog.io/adoptopenjdk/api/gpg/key/public | sudo apt-key add -
#   sudo add-apt-repository --yes https://adoptopenjdk.jfrog.io/adoptopenjdk/deb/
#   sudo apt-get update && sudo apt-get install adoptopenjdk-8-hotspot
#
# For Fedora 36-ish distros:
#  # Prep yum repository from https://adoptium.net/installation/linux/
#  sudo dnf install -y ant temurin-8-jdk
#  export JAVA_HOME=/usr/lib/jvm/temurin-8-jdk

sinfo() { echo "$@" >&2 ; }
shead() { sinfo "" ; sinfo "---------------------------------" ; sinfo "-- $@" ; sinfo "---------------------------------" ; }

this_script="$(realpath "${BASH_SOURCE[0]}")"
script_dir="$(realpath "$(dirname "$this_script")")"
qmk_firmware_dir="$(realpath "$script_dir/../")"

export PATH="$PATH:$script_dir/fmpp/bin"

build_fmpp() {
    [ -f "$script_dir/fmpp.tar.gz" ] \
        || wget -O"$script_dir/fmpp.tar.gz" https://github.com/freemarker/fmpp/archive/v0.9.16.tar.gz
    [ -d "$script_dir/fmpp" ] \
        || { mkdir "$script_dir/fmpp" && tar xf "$script_dir/fmpp.tar.gz" -C "$script_dir/fmpp" --strip-components=1 ; }
    pushd "$script_dir/fmpp" >/dev/null 2>&1
    sed -e "s#bootclasspath.path=.*#bootclasspath.path=$(find /usr/lib/jvm -name 'rt.jar' | sort | tail -n1)#g" \
        -e "s#ant.jar.path=.*#ant.jar.path=$(find /usr/share/java -name 'ant-1*.jar' -or -name 'ant.jar' | sort | tail -n1)#g" \
        build.properties.sample > build.properties
    sed -e 's#source="1.5"#source="1.8"#g' \
        -e 's#target="1.5"#target="1.8"#g' \
        build.xml > build.xml.new
    mv build.xml.new build.xml
    ant clean
    ant
    chmod +x "$script_dir/fmpp/bin/fmpp"
    popd >/dev/null 2>&1
}

find_chibi_files() {
    local search_path="$1"
    shift
    local conditions=( "$@" )
    for file in $(find -L "$search_path" -not -path '*/lib/chibios*' -and -not -path '*/util/*' -and \( "${conditions[@]}" \) | sort) ; do
        if [ -z "$(grep 'include_next' "$file")" ] ; then
            echo $file
        fi
    done
}

upgrade_conf_files_generic() {
    local search_filename="$1"
    local update_script="$2"
    shead "Updating $search_filename files ($update_script)..."
    pushd "$qmk_firmware_dir/lib/chibios/tools/updater" >/dev/null 2>&1
    for file in $(find_chibi_files "$qmk_firmware_dir" -name "$search_filename") ; do
        cp -f "$file" "$file.orig"
        clang-format --style='{IndentPPDirectives: None}' -i "$file"
        cp -f "$file" "$file.formatted"
        bash "$update_script" "$file"
        if ! diff "$file" "$file.formatted" >/dev/null 2>&1 ; then
            dos2unix "$file" >/dev/null 2>&1
        else
            cp -f "$file.orig" "$file"
        fi
        rm -f "$file.orig" "$file.formatted"
    done
    popd >/dev/null 2>&1
}

upgrade_chconf_files() {
    upgrade_conf_files_generic chconf.h update_chconf_rt.sh
}

upgrade_halconf_files() {
    upgrade_conf_files_generic halconf.h update_halconf.sh

    OIFS=$IFS
    IFS=$'\n'
    for file in $(find_chibi_files "$qmk_firmware_dir" -name halconf.h) ; do
        echo $file
        sed -i 's@#include "mcuconf.h"@#include <mcuconf.h>@g' "$file"
    done
    IFS=$OIFS
}

upgrade_mcuconf_files() {
    pushd "$qmk_firmware_dir/lib/chibios/tools/updater" >/dev/null 2>&1
    for f in $(find . -name 'update_mcuconf*') ; do
        upgrade_conf_files_generic mcuconf.h $f
    done
    popd >/dev/null 2>&1
}

hash -r
[[ -n "$(which fmpp 2>/dev/null)" ]] || build_fmpp

upgrade_mcuconf_files
upgrade_chconf_files
upgrade_halconf_files
