#!/bin/bash

set -eEuo pipefail
umask 022

sinfo() { echo "$@" >&2 ; }
shead() { sinfo "" ; sinfo "---------------------------------" ; sinfo "-- $@" ; sinfo "---------------------------------" ; }
havecmd()  { command command type "${1}" >/dev/null 2>&1 || return 1 ; }

this_script="$(realpath "${BASH_SOURCE[0]}")"
script_dir="$(realpath "$(dirname "$this_script")")"
qmk_firmware_dir="$(realpath "$script_dir/../")"

declare -A file_hashes

export PATH="$PATH:$script_dir/fmpp/bin"

build_fmpp() {
    [ -f "$script_dir/fmpp.tar.gz" ] \
        || wget -O"$script_dir/fmpp.tar.gz" https://github.com/freemarker/fmpp/archive/v0.9.16.tar.gz
    [ -d "$script_dir/fmpp" ] \
        || { mkdir "$script_dir/fmpp" && tar xf "$script_dir/fmpp.tar.gz" -C "$script_dir/fmpp" --strip-components=1 ; }
    pushd "$script_dir/fmpp" >/dev/null 2>&1
    sed -e "s#bootclasspath.path=.*#bootclasspath.path=$(find /usr/lib/jvm -name 'rt.jar' | sort | tail -n1)#g" \
        -e "s#ant.jar.path=.*#ant.jar.path=$(find /usr/share/java -name 'ant-1*.jar' | sort | tail -n1)#g" \
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
    find "$search_path" -not -path '*/lib/chibios*' -and -not -path '*/lib/ugfx*' -and -not -path '*/util/*' -and \( "${conditions[@]}" \) | sort
}

revert_chibi_files() {
    local search_path="$1"
    shead "Reverting ChibiOS config/board files..."
    for file in $(find_chibi_files "$search_path" -name chconf.h -or -name halconf.h -or -name mcuconf.h -or -name board.c -or -name board.h -or -name board.mk -or -name board.chcfg) ; do
        pushd "$search_path" >/dev/null 2>&1
        local relpath=$(realpath --relative-to="$search_path" "$file")
        git checkout upstream/master -- "$relpath" || git checkout origin/master -- "$relpath" || true
        popd >/dev/null 2>&1
    done
}

populate_file_hashes() {
    local search_path="$1"
    shead "Determining duplicate config/board files..."
    for file in $(find_chibi_files "$search_path" -name chconf.h -or -name halconf.h -or -name mcuconf.h -or -name board.c -or -name board.h) ; do
        local key="file_$(clang-format "$file" | sha1sum | cut -d' ' -f1)"
        local relpath=$(realpath --relative-to="$search_path" "$file")
        file_hashes[$key]="${file_hashes[$key]:-} $relpath"
    done
    for file in $(find_chibi_files "$search_path" -name board.mk -or -name board.chcfg) ; do
        local key="file_$(cat "$file" | sha1sum | cut -d' ' -f1)"
        local relpath=$(realpath --relative-to="$search_path" "$file")
        file_hashes[$key]="${file_hashes[$key]:-} $relpath"
    done
}

determine_equivalent_files() {
    local search_file="$1"
    for K in "${!file_hashes[@]}"; do
        for V in ${file_hashes[$K]}; do
            if [[ "$V" == "$search_file" ]] ; then
                for V in ${file_hashes[$K]}; do
                    echo "$V"
                done
                return 0
            fi
        done
    done
    return 1
}

deploy_staged_files() {
    shead "Deploying staged files..."
    for file in $(find "$qmk_firmware_dir/util/chibios-upgrade-staging" -type f) ; do
        local relpath=$(realpath --relative-to="$qmk_firmware_dir/util/chibios-upgrade-staging" "$file")
        sinfo "Deploying staged file: $relpath"
        for other in $(determine_equivalent_files "$relpath") ; do
            sinfo "    => $other"
            cp "$qmk_firmware_dir/util/chibios-upgrade-staging/$relpath" "$qmk_firmware_dir/$other"
        done
    done
}

swap_mcuconf_f3xx_f303() {
    shead "Swapping STM32F3xx_MCUCONF -> STM32F303_MCUCONF..."
    for file in $(find_chibi_files "$qmk_firmware_dir" -name mcuconf.h) ; do
        sed -i 's#STM32F3xx_MCUCONF#STM32F303_MCUCONF#g' "$file"
        dos2unix "$file" >/dev/null 2>&1
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
}

upgrade_mcuconf_files() {
    pushd "$qmk_firmware_dir/lib/chibios/tools/updater" >/dev/null 2>&1
    for f in $(find . -name 'update_mcuconf*') ; do
        upgrade_conf_files_generic mcuconf.h $f
    done
    popd >/dev/null 2>&1
}

update_staged_files() {
    shead "Updating staged files with ChibiOS upgraded versions..."
    for file in $(find "$qmk_firmware_dir/util/chibios-upgrade-staging" -type f) ; do
        local relpath=$(realpath --relative-to="$qmk_firmware_dir/util/chibios-upgrade-staging" "$file")
        sinfo "Updating staged file: $relpath"
        cp "$qmk_firmware_dir/$relpath" "$qmk_firmware_dir/util/chibios-upgrade-staging/$relpath"
    done
}

havecmd fmpp || build_fmpp
revert_chibi_files "$qmk_firmware_dir"
populate_file_hashes "$qmk_firmware_dir"

shead "Showing duplicate ChibiOS files..."
for K in "${!file_hashes[@]}"; do
    sinfo ${K#file_}:
    for V in ${file_hashes[$K]}; do
        sinfo "    $V"
    done
done

if [ "${1:-}" == "-r" ] ; then
    exit 0
fi

swap_mcuconf_f3xx_f303

deploy_staged_files
upgrade_mcuconf_files
upgrade_chconf_files
upgrade_halconf_files
update_staged_files
