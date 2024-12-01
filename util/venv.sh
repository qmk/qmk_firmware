#!/usr/bin/env bash
# This script is used to setup a virtual environment for QMK use, and subsequently allows running `qmk` commands from the virtual environment.

# Exit on error
set -eEuo pipefail
umask 022

# Find the QMK firmware directory
this_script=$(realpath "${BASH_SOURCE[0]}")
this_dir=$(dirname "$this_script")
qmk_firmware_dir=$(realpath "$this_dir/..")

# Allow overriding the virtual environment directory from the environment, if necessary
if [ -z "${QMK_VENV_DIR:-}" ]; then
    QMK_VENV_DIR="$qmk_firmware_dir/.venv"
fi

# Switch to the QMK firmware directory
cd "$qmk_firmware_dir"

# Check if the virtual environment exists
if [ ! -d "$QMK_VENV_DIR" ]; then
    echo "Creating virtual environment..."
    python3 -m venv "$QMK_VENV_DIR"
fi

# Activate the virtual environment
source "$QMK_VENV_DIR/bin/activate"

# Install qmk into the venv if it's not already installed
if [[ ! -e "$QMK_VENV_DIR/bin/qmk" ]]; then
    echo "Installing QMK CLI..."
    pip install --require-virtualenv --quiet --no-input --upgrade pip qmk
    pip install --require-virtualenv --quiet --no-input --upgrade -r requirements-dev.txt
fi

# Run the arguments as if it were a `qmk` command
exec "$@"
