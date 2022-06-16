/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include <system.h>
#include <io.h>
#include <string.h>
#include "gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT			GDISPVMT_alteraframereader
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"
#include "board_alteraframereader.h"

#ifndef FRAMEREADER_BASE
	#error "Framereader IP base address (FRAMEREADER_BASE) not set in board file."
#endif
#ifndef SCREEN_WIDTH
	#error "Screen width (SCREEN_WIDTH) not set in board file."
#endif
#ifndef SCREEN_HEIGHT
	#error "Screen height (SCREEN_HEIGHT) not set in board file."
#endif

typedef struct fbPriv {
	void* pixels;			// The pixel buffer
	gCoord linelen;		// The number of bytes per display line
	void* frame0;
	void* frame1;
} fbPriv;

/*===========================================================================*/
/* Driver local routines    .                                                */
/*===========================================================================*/

#define PIXIL_POS(g, x, y)      ((y) * ((fbPriv *)(g)->priv)->linelen + (x) * sizeof(LLDCOLOR_TYPE))
#define PIXEL_ADDR(g, pos)      ((LLDCOLOR_TYPE *)(((char *)((fbPriv *)(g)->priv)->pixels)+pos))
#define PRIV(g)                 ((fbPriv *)g->priv)

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

LLDSPEC gBool gdisp_lld_init(GDisplay* g)
{
	// Allocate the frame buffers
	PRIV(g)->frame0 = gfxAlloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(LLDCOLOR_TYPE));
	PRIV(g)->frame1 = gfxAlloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(LLDCOLOR_TYPE));
	if (!PRIV(g)->frame0 || !PRIV(g)->frame1) {
		gfxHalt("Couldn't allocate memory for framebuffer\r\n");
	}

	// Initialize the private structure
	g->g.Width = SCREEN_WIDTH;
	g->g.Height = SCREEN_HEIGHT;
	g->g.Backlight = 100;
	g->g.Contrast = 50;
	g->g.Orientation = gOrientation0;
	g->g.Powermode = gPowerOn;
	g->board = 0;
	PRIV(g)->linelen = g->g.Width * sizeof(LLDCOLOR_TYPE);	// bytes per line
	PRIV(g)->pixels = PRIV(g)->frame0;
	
	// Make sure the MSB is set so we bypass the data cache of the NIOS-II soft core
	PRIV(g)->pixels = (void*)((char*)PRIV(g)->pixels + 0x80000000);
	
	// Stop the framereader to allow for configuration
	IOWR(ALT_VIP_VFR_0_BASE, 0x00, 0x00); // stop for config

	// Frame 0
	IOWR(ALT_VIP_VFR_0_BASE, 0x04, (gU32)PRIV(g)->frame0);	
	IOWR(ALT_VIP_VFR_0_BASE, 0x05, SCREEN_WIDTH*SCREEN_HEIGHT/2);
	IOWR(ALT_VIP_VFR_0_BASE, 0x06, SCREEN_WIDTH*SCREEN_HEIGHT);	
	IOWR(ALT_VIP_VFR_0_BASE, 0x08, SCREEN_WIDTH);
	IOWR(ALT_VIP_VFR_0_BASE, 0x09, SCREEN_HEIGHT);
	IOWR(ALT_VIP_VFR_0_BASE, 0x0a, 0x00);
	
	// Frame 1
	IOWR(ALT_VIP_VFR_0_BASE, 0x0b, (gU32)PRIV(g)->frame1);	
	IOWR(ALT_VIP_VFR_0_BASE, 0x0c, SCREEN_WIDTH*SCREEN_HEIGHT/2);
	IOWR(ALT_VIP_VFR_0_BASE, 0x0d, SCREEN_WIDTH*SCREEN_HEIGHT);	
	IOWR(ALT_VIP_VFR_0_BASE, 0x0f, SCREEN_WIDTH);
	IOWR(ALT_VIP_VFR_0_BASE, 0x10, SCREEN_HEIGHT);
	IOWR(ALT_VIP_VFR_0_BASE, 0x11, 0x00);

	// Select frame0 (user draws to frame0 -> double buffering disabled by default)
	IOWR(ALT_VIP_VFR_0_BASE, 0x03, 0x00);

	// Start the framebuffer reader
	IOWR(ALT_VIP_VFR_0_BASE, 0x00, 0x01);

	return gTrue;
}

LLDSPEC void gdisp_lld_draw_pixel(GDisplay* g)
{
	unsigned	pos;

	#if GDISP_NEED_CONTROL
		switch(g->g.Orientation) {
		case gOrientation0:
		default:
			pos = PIXIL_POS(g, g->p.x, g->p.y);
			break;
		case gOrientation90:
			pos = PIXIL_POS(g, g->p.y, g->g.Width-g->p.x-1);
			break;
		case gOrientation180:
			pos = PIXIL_POS(g, g->g.Width-g->p.x-1, g->g.Height-g->p.y-1);
			break;
		case gOrientation270:
			pos = PIXIL_POS(g, g->g.Height-g->p.y-1, g->p.x);
			break;
		}
	#else
		pos = PIXIL_POS(g, g->p.x, g->p.y);
	#endif

		PIXEL_ADDR(g, pos)[0] = gdispColor2Native(g->p.color);
}

LLDSPEC	gColor gdisp_lld_get_pixel_color(GDisplay* g)
{
	unsigned		pos;
	LLDCOLOR_TYPE	color;

	#if GDISP_NEED_CONTROL
		switch(g->g.Orientation) {
		case gOrientation0:
		default:
			pos = PIXIL_POS(g, g->p.x, g->p.y);
			break;
		case gOrientation90:
			pos = PIXIL_POS(g, g->p.y, g->g.Width-g->p.x-1);
			break;
		case gOrientation180:
			pos = PIXIL_POS(g, g->g.Width-g->p.x-1, g->g.Height-g->p.y-1);
			break;
		case gOrientation270:
			pos = PIXIL_POS(g, g->g.Height-g->p.y-1, g->p.x);
			break;
		}
	#else
		pos = PIXIL_POS(g, g->p.x, g->p.y);
	#endif

	color = PIXEL_ADDR(g, pos)[0];
	return gdispNative2Color(color);
}

#if GDISP_NEED_CONTROL
	LLDSPEC void gdisp_lld_control(GDisplay* g)
	{
		switch(g->p.x) {
		case GDISP_CONTROL_POWER:
			if (g->g.Powermode == (gPowermode)g->p.ptr)
				return;
			switch((gPowermode)g->p.ptr) {
			case gPowerOff: case gPowerOn: case gPowerSleep: case gPowerDeepSleep:
				board_power(g, (gPowermode)g->p.ptr);
				break;
			default:
				return;
			}
			g->g.Powermode = (gPowermode)g->p.ptr;
			return;

		case GDISP_CONTROL_ORIENTATION:
			if (g->g.Orientation == (gOrientation)g->p.ptr)
				return;
			switch((gOrientation)g->p.ptr) {
				case gOrientation0:
				case gOrientation180:
					if (g->g.Orientation == gOrientation90 || g->g.Orientation == gOrientation270) {
						gCoord		tmp;

						tmp = g->g.Width;
						g->g.Width = g->g.Height;
						g->g.Height = tmp;
					}
					break;
				case gOrientation90:
				case gOrientation270:
					if (g->g.Orientation == gOrientation0 || g->g.Orientation == gOrientation180) {
						gCoord		tmp;

						tmp = g->g.Width;
						g->g.Width = g->g.Height;
						g->g.Height = tmp;
					}
					break;
				default:
					return;
			}
			g->g.Orientation = (gOrientation)g->p.ptr;
			return;

		case GDISP_CONTROL_BACKLIGHT:
			if ((unsigned)g->p.ptr > 100) g->p.ptr = (void *)100;
			board_backlight(g, (unsigned)g->p.ptr);
			g->g.Backlight = (unsigned)g->p.ptr;
			return;

		case GDISP_CONTROL_CONTRAST:
			if ((unsigned)g->p.ptr > 100) g->p.ptr = (void *)100;
			board_contrast(g, (unsigned)g->p.ptr);
			g->g.Contrast = (unsigned)g->p.ptr;
			return;

		case GDISP_CONTROL_BUFFERS_SWAP:
			if (PRIV(g)->pixels == PRIV(g)->frame0) {
				PRIV(g)->pixels = PRIV(g)->frame1;
				IOWR(ALT_VIP_VFR_0_BASE, 0x03, 0x00);
			} else {
				PRIV(g)->pixels = PRIV(g)->frame0;
				IOWR(ALT_VIP_VFR_0_BASE, 0x03, 0x01);
			}
			return;
			
		case GDISP_CONTROL_BUFFERS_ENABLE:
			// Display frame0, draw to frame1
			PRIV(g)->pixels = PRIV(g)->frame1;
			IOWR(ALT_VIP_VFR_0_BASE, 0x03, 0x00);
			return;

		case GDISP_CONTROL_BUFFERS_DISABLE:
			// Display frame0, draw to frame0
			PRIV(g)->pixels = PRIV(g)->frame0;
			IOWR(ALT_VIP_VFR_0_BASE, 0x03, 0x00);
			return;
		}
	}
#endif

#if GDISP_HARDWARE_FILLS
	LLDSPEC void gdisp_lld_fill_area(GDisplay* g)
	{
		int i;
		unsigned int addr;
		int bytes_per_line;
		int bytes_per_pixel;
		gU8* line;
	
		// Calculate some values required for further calculations
		bytes_per_pixel = ((fbPriv*)g->priv)->linelen/g->g.Width; // must be 4
		bytes_per_line = ((fbPriv*)g->priv)->linelen;
	
		// Allocate line buffer
		line = gfxAlloc(bytes_per_pixel * g->p.cx);
	
		// Fill the line buffer with the solid color
	    for (i = 0; i < bytes_per_pixel * g->p.cx; i += 4)  {
			*((gColor*)(line + i)) = g->p.color;
		}
	  
		// Calculate the address of the first pixel of the rectangle (top left corner)
		addr = (int)((char *)((fbPriv *)g->priv)->pixels + (g->p.y * bytes_per_line) + (g->p.x * bytes_per_pixel));
	
		// Copy filled line buffer to create rectangle
		for (i = 0; i < g->p.cy; i++) {
			memcpy((void*)addr, line, bytes_per_pixel * g->p.cx);
			addr += bytes_per_line;
		}
	
		// Free the line buffer
		gfxFree(line);		
	}
#endif	// GDISP_HARDWARE_FILLS

#endif /* GFX_USE_GDISP */
