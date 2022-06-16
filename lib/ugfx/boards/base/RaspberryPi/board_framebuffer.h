/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */


// Set this to your frame buffer pixel format and size. You can also override these in your makefile.
#ifndef GDISP_LLD_PIXELFORMAT
	#define GDISP_LLD_PIXELFORMAT		GDISP_PIXELFORMAT_RGB565
#endif
#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH			800
#endif
#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT			600
#endif

#ifdef GDISP_DRIVER_VMT

	#if GDISP_SCREEN_WIDTH > 4096 || GDISP_SCREEN_HEIGHT > 4096
		#error "Raspberry Pi Framebuffer: Screen size is defined too large. Max is 4096x4096"
	#endif

	#include "rpi_mailbox.h"

	typedef struct FrameBufferDescription {
		gU32	width;
		gU32	height;
		gU32	vWidth;
		gU32	vHeight;
		gU32	pitch;
		gU32	bitDepth;
		gU32	x;
		gU32	y;
		void *		pointer;
		gU32	size;
		} FrameBufferDescription;

	static FrameBufferDescription FrameBufferInfo __attribute__((aligned (16))) = { 1024, 768, 1024, 768, 0, 24, 0, 0, 0, 0 };

	static void board_init(GDisplay *g, fbInfo *fbi) {
		// Initialize the Raspberry Pi frame buffer

		FrameBufferInfo.width = GDISP_SCREEN_WIDTH;
		FrameBufferInfo.height = GDISP_SCREEN_HEIGHT;
		FrameBufferInfo.vWidth = GDISP_SCREEN_WIDTH;
		FrameBufferInfo.vHeight = GDISP_SCREEN_HEIGHT;
		FrameBufferInfo.bitDepth = LLDCOLOR_BITS;

		rpi_writemailbox(1, 0x40000000 + (gU32) &FrameBufferInfo);

		if (rpi_readmailbox(1) != 0)
			gfxHalt("Could not set display parameters")
	
		// Set the details of the frame buffer
		g->g.Width = GDISP_SCREEN_WIDTH;
		g->g.Height = GDISP_SCREEN_HEIGHT;
		g->g.Backlight = 100;
		g->g.Contrast = 50;
		fbi->linelen = g->g.Width * sizeof(LLDCOLOR_TYPE);	// bytes per row
		fbi->pixels = FrameBufferInfo.pointer;				// pointer to the memory frame buffer
	}

	#if GDISP_HARDWARE_FLUSH
		static void board_flush(GDisplay *g) {
			(void) g;
		}
	#endif

	#if GDISP_NEED_CONTROL
		static void board_backlight(GDisplay *g, gU8 percent) {
			(void) g;
			(void) percent;
		}

		static void board_contrast(GDisplay *g, gU8 percent) {
			(void) g;
			(void) percent;
		}

		static void board_power(GDisplay *g, gPowermode pwr) {
			(void) g;
			(void) pwr;
		}
	#endif

#endif /* GDISP_DRIVER_VMT */
