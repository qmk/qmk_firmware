#!/bin/bash

util_dir=$(dirname "$0")

if ! brew --version 2>&1 > /dev/null; then
	echo "Error! Homebrew not installed or broken!"
	echo -n "Would you like to install homebrew now? [y/n] "
	while read ANSWER; do
		case $ANSWER in
			y|Y)
				/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
				break
			;;
			n|N)
				exit 1
			;;
			*)
				echo -n "Would you like to install homebrew now? [y/n] "
			;;
		esac
	done
fi

# All macOS dependencies are managed in the homebrew package:
#     https://github.com/qmk/homebrew-qmk
brew update
brew install qmk/qmk/qmk
brew link --force avr-gcc@8

pip3 install -r "${util_dir}/../requirements.txt"
