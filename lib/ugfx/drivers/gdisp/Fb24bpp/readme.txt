To use this driver:

1. Add in your gfxconf.h:
	a) #define GFX_USE_GDISP		GFXON

2. To your makefile add the following lines:
	include $(GFXLIB)/gfx.mk
	include $(GFXLIB)/drivers/gdisp/Fb24bpp/driver.mk

3. Add a board_fb24bpp.h to you project directory (or board directory)
	base on one of the templates.

Note: This driver supports RGB888 and BGR888 packed framebuffer formats.
