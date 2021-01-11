#!/bin/sh
util_dir=$(dirname "$0")
pkg update
pkg install -y \
	git \
	wget \
	gmake \
	gcc \
	zip \
	unzip \
	avr-binutils \
	avr-gcc \
	avr-libc \
	dfu-programmer \
	dfu-util \
	arm-none-eabi-gcc \
	arm-none-eabi-binutils \
	arm-none-eabi-newlib \
	diffutils \
	python3
pip3 install -r ${util_dir}/../requirements.txt
