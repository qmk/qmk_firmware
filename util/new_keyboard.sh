#!/usr/bin/env bash

# This script generates a new keyboard directory under keyboards/,
# and copies the template files from data/templates/ into it.

# Print an error message with the word "ERROR" in red.
echo_error() {
    echo -e "[\033[0;91mERROR\033[m]: $1"
}

# Print a message in bold.
echo_bold() {
    echo -e "\033[1m$1\033[m"
}

# Prompt the user for information, showing the default value in brackets.
prompt() {
    local message="$1"
    local default="$2"

    [ -n "$default" ] && message+=" [$default]"
    message+=": "

    read -rp "$message" prompt_return
    [ -z "$prompt_return" ] && prompt_return="$default"
}

# Grab a username from Git config.
set_git_username() {
    git_username="$(git config --get user.name)"
}

# Copy the template files to the new keyboard directory.
copy_templates() {
    mkdir -p "$keyboard_dir"

    echo -n "Copying base template files..."
    cp -r "data/templates/base/." "${keyboard_dir}"
    echo " done"

    echo -n "Copying $keyboard_type template files..."
    cp -r "data/templates/${keyboard_type}/." "${keyboard_dir}"
    echo " done"

    echo -n "Renaming keyboard files..."
    mv "${keyboard_dir}/keyboard.c" "${keyboard_dir}/${keyboard_base_name}.c"
    mv "${keyboard_dir}/keyboard.h" "${keyboard_dir}/${keyboard_base_name}.h"
    echo " done"
}

# Set the inplace editing parameter for sed.
# macOS/BSD sed expects a file extension immediately following -i.
set_sed_i() {
    sed_i=(-i)

    case $(uname -a) in
        *Darwin*) sed_i=(-i "")
    esac
}

# Replace a token with a value in the given list of files.
replace_placeholders() {
    local replace_token="$1"
    local replace_value="$2"
    shift 2
    local replace_filenames=("$@")

    echo -n "Replacing $replace_token with $replace_value..."
    for replace_filename in "${replace_filenames[@]}"; do
        sed "${sed_i[@]}" -e "s/${replace_token}/${replace_value}/g" "$replace_filename"
    done
    echo " done"
}

# Replace %YEAR% with the current year.
replace_year_placeholders() {
    local replace_year_filenames=(
        "${keyboard_dir}/config.h"
        "${keyboard_dir}/${keyboard_base_name}.c"
        "${keyboard_dir}/${keyboard_base_name}.h"
        "${keyboard_dir}/keymaps/default/keymap.c"
    )
    replace_placeholders "%YEAR%" "$(date +%Y)" "${replace_year_filenames[@]}"
}

# Replace %KEYBOARD% with the keyboard name.
replace_keyboard_placeholders() {
    local replace_keyboard_filenames=(
        "${keyboard_dir}/config.h"
        "${keyboard_dir}/info.json"
        "${keyboard_dir}/readme.md"
        "${keyboard_dir}/${keyboard_base_name}.c"
        "${keyboard_dir}/keymaps/default/readme.md"
    )
    replace_placeholders "%KEYBOARD%" "$keyboard_base_name" "${replace_keyboard_filenames[@]}"
}

# Replace %YOUR_NAME% with the username.
replace_name_placeholders() {
    local replace_name_filenames=(
        "${keyboard_dir}/config.h"
        "${keyboard_dir}/info.json"
        "${keyboard_dir}/readme.md"
        "${keyboard_dir}/${keyboard_base_name}.c"
        "${keyboard_dir}/${keyboard_base_name}.h"
        "${keyboard_dir}/keymaps/default/keymap.c"
    )
    replace_placeholders "%YOUR_NAME%" "$username" "${replace_name_filenames[@]}"
}

# Check if an array contains an element.
array_contains() {
    local e match="$1"
    shift
    for e; do
        [[ "$e" == "$match" ]] && return 0;
    done

    return 1
}

# If we've been started from util/, we want to be in qmk_firmware/
[[ "$PWD" == *util ]] && cd ..

# The root qmk_firmware/ directory should have a subdirectory called quantum/
if [ ! -d "quantum" ]; then
    echo_error "Could not detect the QMK firmware directory!"
    echo_error "Are you sure you're in the right place?"
    exit 1
fi

echo_bold "########################################"
echo_bold "#                NOTICE                #"
echo_bold "#   This script has been deprecated.   #"
echo_bold "# Please use qmk new-keyboard instead. #"
echo_bold "########################################"
echo
echo_bold "Generating a new QMK keyboard directory"
echo

# Keyboard name is required, so keep prompting until we get one
while [ -z "$keyboard_name" ]; do
    prompt "Keyboard Name" ""
    keyboard_name=$prompt_return
    keyboard_base_name=$(basename $keyboard_name)
done

keyboard_dir="keyboards/$keyboard_name"

if [ -d "$keyboard_dir" ]; then
    echo_error "Keyboard $keyboard_name already exists!"
    exit 1
fi

KEYBOARD_TYPES=("avr" "ps2avrgb")

prompt "Keyboard Type" "avr"
keyboard_type=$prompt_return

if ! array_contains "$keyboard_type" "${KEYBOARD_TYPES[@]}"; then
    echo_error "Keyboard type must be one of: ${KEYBOARD_TYPES[*]}"
    exit 1
fi

set_git_username
prompt "Your Name" "$git_username"
username=$prompt_return

echo

copy_templates
set_sed_i
replace_year_placeholders
replace_keyboard_placeholders
[ -n "$username" ] && replace_name_placeholders

echo
echo_bold "Created a new keyboard called $keyboard_name."
echo
echo_bold "To start working on things, cd into keyboards/$keyboard_name,"
echo_bold "or open the directory in your favourite text editor."
