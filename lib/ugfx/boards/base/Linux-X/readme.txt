This directory contains the interface for Linux using X.


On this board uGFX currently supports:
	- GDISP via the X driver 
	- GINPUT-touch via the X driver


The folowing packages are required to run uGFX using this driver on
a 64-bit Linux system running X:
	+ gcc-multilib
	+ build-essential
	+ xorg-dev
	+ libx11-dev
	+ libx11-dev:i386


There is an example Makefile and project in the examples directory.
