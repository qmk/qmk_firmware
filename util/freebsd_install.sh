#!/bin/sh
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
