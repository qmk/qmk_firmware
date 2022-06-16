This directory contains the interface for Linux using SDL.

On this board uGFX currently supports:
	- GDISP via the SDL driver
	- GINPUT-touch via the SDL driver
	- GINPUT-keyboard via the SDL driver


The folowing packages are required to run uGFX using this driver on
a 64-bit Linux system using SDL:
	+ gcc-multilib
	+ build-essential
	+ libsdl2-dev:i386


The following should be added to the CFLAGS of the target makefile:
	CFLAGS = `sdl2-config --libs --cflags`


There is an example Makefile and project in the examples directory.
