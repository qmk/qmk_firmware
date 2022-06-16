This driver can be used for the "Frame Reader IP Core" that comes with the "Video and Image Processing Suite" package
from Altera/Intel/Quartus.

This driver takes advantage of the double buffering feature offered by the "Frame Reader IP Core". The following commands
can be used through the gdispControl() API to manage the two frame buffers:

	gdispControl(GDISP_CONTROL_BUFFERS_ENABLE, 0);		// Enabel the two framebuffers (Disabled by default)
	gdispControl(GDISP_CONTROL_BUFFERS_DISABLE, 0);		// Disable the two framebuffers (Disabled by default)
	gdispControl(GDISP_CONTROL_BUFFERS_SWAP, 0);		// Swap the framebuffers (if enabled)

The double buffering is taken care of completely by the driver. It sets the framebuffer pointers correctly so that it's
transparent to the application. There's no need to handle the two framebuffers manually through the multiple displays
support offered by uGFX. Using GDISP_CONTROL_BUFFERS_SWAP will swap the framebuffers on the actual hardware as well
as swap the framebuffer pointers for the default GDisplay to draw to the other framebuffer. 


To use this driver:

1. Add in your gfxconf.h:
	a) #define GFX_USE_GDISP		GFXON

2. To your makefile add the following lines:
	include $(GFXLIB)/gfx.mk
	include $(GFXLIB)/drivers/gdisp/AlteraFramereader/driver.mk

3. Add a board_alteraframereader.h to you project directory (or board directory)
	base on one of the templates found in this drivers directory.
