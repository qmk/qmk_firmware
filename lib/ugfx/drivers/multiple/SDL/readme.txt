To use this driver:

This driver is special in that it implements both the gdisp low level driver
and a touchscreen driver.

1. Add in your gfxconf.h:
	a) #define GFX_USE_GDISP			GFXON
	b) #define GFX_USE_GINPUT			GFXON
		#define GINPUT_USE_MOUSE		GFXON
	c) Any optional high level driver defines (see gdisp.h) eg: GDISP_NEED_MULTITHREAD
	d) Optionally the following (with appropriate values):
		#define GDISP_SCREEN_WIDTH	640
		#define GDISP_SCREEN_HEIGHT	480

2. To your makefile add the following lines:
	include $(GFXLIB)/gfx.mk
	include $(GFXLIB)/drivers/multiple/SDL/gdisp_lld.mk

3. Install sdl2
	on Linux:
		sudo apt-get install libsdl2-dev
	on OSX:
		brew install sdl2 --universal

4. Modify your makefile to add `sdl2-config --libs --cflags` to the CFLAGS line. i.e.
	CFLAGS = `sdl2-config --libs --cflags`
