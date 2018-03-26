#!/bin/bash

set -x

if ! doxygen -v 2>&1 > /dev/null; then
	echo "doxygen not found! Please install it!"
	exit 1
elif ! moxygen -V 2>&1 > /dev/null; then
	echo -n "moxygen not found! Would you like to install it? [y/n] "
	read ANSWER
	case $ANSWER in
		y|Y|yes|YES|Yes)
			npm install -g moxygen
		;;
		*)
			exit 1
		;;
	esac
fi

if [ ! -e Doxyfile ]; then
	echo "Error: You must run this from the top-level qmk_firmware directory!"
	exit 1
fi

# Generate the doxygen XML files
rm -rf doxygen
doxygen Doxyfile

# Generate the moxygen Markdown files
moxygen -a -g -o docs/internals_%s.md doxygen/xml
