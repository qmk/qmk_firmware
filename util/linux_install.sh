#!/bin/sh

if grep ID /etc/os-release | grep -q rhel; then
	# RPM based OS
	sudo dnf install gcc unzip wget zip dfu-util dfu-programmer avr-gcc \
	    avr-libc binutils-avr32-linux-gnu arm-none-eabi-gcc-cs \
	    arm-none-eabi-binutils-cs arm-none-eabi-newlib
elif grep ID /etc/os-release | grep -q debian; then
	sudo apt-get update
	sudo apt-get install gcc unzip wget zip gcc-avr binutils-avr avr-libc \
	    dfu-programmer dfu-util gcc-arm-none-eabi binutils-arm-none-eabi \
	    libnewlib-arm-none-eabi
else
	echo "Sorry, we don't recognize your OS. Help us by contributing support!"
	echo
	echo "    https://docs.qmk.fm/contributing.html"
fi
