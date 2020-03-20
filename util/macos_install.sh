#!/bin/bash

util_dir=$(dirname "$0")

if ! brew --version >/dev/null 2>&1; then
	echo "Error! Homebrew not installed or broken!"
	echo -n "Would you like to install homebrew now? [y/n] "
	while read -r ANSWER; do
		case $ANSWER in
		y | Y)
			/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
			break
			;;
		n | N)
			exit 1
			;;
		*)
			echo -n "Would you like to install homebrew now? [y/n] "
			;;
		esac
	done
fi

brew tap osx-cross/avr
brew tap osx-cross/arm
brew update
brew install avr-gcc@8 arm-gcc-bin@8 dfu-programmer avrdude clang-format dfu-util python3
brew install --HEAD https://raw.githubusercontent.com/robertgzr/homebrew-tap/master/bootloadhid.rb
brew link --force avr-gcc@8
brew link --force arm-gcc-bin@8

pip3 install -r "${util_dir}/../requirements.txt"
