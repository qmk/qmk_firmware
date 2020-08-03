#!/bin/bash

# This script finds all rules.mk files in keyboards/ subdirectories,
# and deletes the build option filesize impacts from them.

# Print an error message with the word "ERROR" in red.
echo_error() {
    echo -e "[\033[0;91mERROR\033[m]: $1"
}

# If we've been started from util/, we want to be in qmk_firmware/
[[ "$PWD" == *util ]] && cd ..

# The root qmk_firmware/ directory should have a subdirectory called quantum/
if [ ! -d "quantum" ]; then
    echo_error "Could not detect the QMK firmware directory!"
    echo_error "Are you sure you're in the right place?"
    exit 1
fi

# Set the inplace editing parameter for sed.
# macOS/BSD sed expects a file extension immediately following -i.
set_sed_i() {
    sed_i=(-i)

    case $(uname -a) in
        *Darwin*) sed_i=(-i "")
    esac
}
set_sed_i

# Exclude keyamps/ directories
files=$(find keyboards -type f -name 'rules.mk' -not \( -path '*/keymaps*' -prune \))

# Edit rules.mk files 
for file in $files; do
  sed "${sed_i[@]}" -e "s/(+[0-9].*)$//g" "$file"
done

echo "Cleaned up rules.mk files."
