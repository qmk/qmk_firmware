#!/bin/sh

if ! brew --version 2>&1 > /dev/null; then
	echo "Error! Homebrew not installed or broken!"
	exit 1
fi

brew tap osx-cross/avr
brew tap PX4/homebrew-px4
brew update
brew install avr-gcc gcc-arm-none-eabi dfu-programmer avrdude
