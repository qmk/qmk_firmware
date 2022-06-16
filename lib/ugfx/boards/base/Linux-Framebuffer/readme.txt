This directory contains the interface for Linux using a framebuffer display.

On this board uGFX currently supports:
	- GDISP via the framebuffer driver 

There is an example Makefile and project in the examples directory.

Note: To successfully use this board file, the user who executes the compiled
      program requires sufficient permission to access the framebuffer device.
      To simplify: You might need to run your compiled uGFX program as root.
