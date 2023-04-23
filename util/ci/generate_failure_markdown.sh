#!/bin/bash

set -e

this_script="$(realpath "${BASH_SOURCE[0]}")"
script_dir="$(realpath "$(dirname "$this_script")")"
qmk_firmware_dir="$(realpath "$script_dir/../../")"

dump_failure_info() {
    local failure_file="$1"
    local keyboard=$(cat "$failure_file" | grep 'CI Metadata: KEYBOARD=' | cut -d= -f2)
    local keymap=$(cat "$failure_file" | grep 'CI Metadata: KEYMAP=' | cut -d= -f2)
    echo "## ${keyboard}:${keymap}"
    echo "\`\`\`"
    cat "$failure_file" | sed -e $'s/\x1b\[[0-9;]*m//g' | grep -v "CI Metadata:" | grep -vP "(Entering|Leaving) directory"
    echo "\`\`\`"
}

for failure_file in $(find "$qmk_firmware_dir/.build" -name 'failed.log.*' | sort); do
    dump_failure_info "$failure_file"
done

exit 0
