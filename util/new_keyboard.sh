#!/bin/bash

# This script generates a new keyboard directory under keyboards/,
# and copies the template files from quantum/template/ into it.

# Print an error message with the word "ERROR" in red.
echo_error() {
    echo -e "[\033[0;91mERROR\033[m]: $1"
}

# Print a message in bold.
echo_bold() {
    echo -e "\033[1m$1\033[m"
}

# check for presence of Python 3.5 or greater
# PYTHON_VERSION = $(python --version | )

echo_bold "This script has been deprecated, and will be deleted in future."
echo_bold "Please use:\n\n    qmk new-keyboard\n"
qmk new-keyboard
exit 100
