To use this driver:

1. Add in your gfxconf.h:
	a) #define GFX_USE_GDISP		GFXON

2. To your makefile add the following lines:
	include $(GFXLIB)/gfx.mk
	include $(GFXLIB)/drivers/gdisp/framebuffer/driver.mk

3. Add a board_framebuffer.h to you project directory (or board directory)
	base on one of the templates.
	
Note: This driver supports framebuffers in byte, word or dword sized pixels.
	It does not support packed pixel formats eg 1, 2, 4, 15 or 24 bits per pixel
	except where the framebuffer format expects those in memory as 1 byte, 2 bytes or 4 bytes per pixel.
	
Note: For RGB888 and BGR888 packed framebuffer formats use the Fb24bpp driver instead.
