This directory contains the interface for Mac OS X using SDL.

On this board uGFX currently supports:
	- GDISP via the SDL driver
	- GINPUT-touch via the SDL driver
	- GINPUT-keyboard via the SDL driver


The folowing packages are required to run uGFX using this driver on
a 64-bit Mac OS X machine using SDL:
	+ sdl2


The following should be added to the CFLAGS of the target makefile:
	CFLAGS = `sdl2-config --libs --cflags`


There is an example Makefile and project in the examples directory.
