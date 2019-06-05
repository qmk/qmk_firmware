#!/bin/bash

# This script generates a new keymap directory under keyboards/<keyboard>/keymaps/,
# and copies the files from the default keymap into it.

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

# Copy the template files to the new keymap directory.
copy_templates() {
    echo -n "Copying default keymap to $keymap_name..."
    cp -r "keyboards/${keyboard_name}/keymaps/default/." "keyboards/${keyboard_name}/keymaps/${keymap_name}"
    echo " done"
}

# If we've been started from util/, we want to be in qmk_firmware/
[[ "$PWD" == *util ]] && cd ..

# The root qmk_firmware/ directory should have a subdirectory called quantum/
if [ ! -d "quantum" ]; then
    echo_error "Could not detect the QMK firmware directory!"
    echo_error "Are you sure you're in the right place?"
    exit 1
fi

echo_bold "Generating a new QMK keymap"
echo

# Keyboard name is required, so keep prompting until we get one
while [ -z "$keyboard_name" ]; do
    prompt "Keyboard Name" ""
    keyboard_name=$prompt_return
done

keyboard_dir="keyboards/$keyboard_name"

if [ ! -d "$keyboard_dir" ]; then
    echo_error "Keyboard $keyboard_name does not exist!"
    exit 1
fi

set_git_username
prompt "Keymap Name" "$git_username"
keymap_name=$prompt_return

keymap_dir="$keyboard_dir/keymaps/$keymap_name"

if [ -d "$keymap_dir" ]; then
    echo_error "Keymap $keymap_name already exists!"
    exit 1
fi

echo

copy_templates

echo
echo_bold "Created a new keymap for $keyboard_name called $keymap_name."
echo
echo_bold "To start working on things, cd into keyboards/$keyboard_name/keymaps/$keymap_name,"
echo_bold "or open the directory in your favourite text editor."
echo
echo_bold "Compile a firmware file with your new keymap by running:"
echo_bold "    make $keyboard_name:$keymap_name"
echo_bold "from the qmk_firmware directory."
