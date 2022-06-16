/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT			GDISPVMT_fb24bpp
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"

typedef struct fbInfo {
	void *			pixels;			// The pixel buffer
	gCoord			linelen;		// The number of bytes per display line
	} fbInfo;

#include "board_fb24bpp.h"

#if GDISP_LLD_PIXELFORMAT != GDISP_PIXELFORMAT_RGB888 && GDISP_LLD_PIXELFORMAT != GDISP_PIXELFORMAT_BGR888
	#error "GDISP Fb24bpp: Only RGB888 and BGR888 color formats are supported by this driver"
#endif

typedef struct fbPriv {
	fbInfo			fbi;			// Display information
	} fbPriv;

/*===========================================================================*/
/* Driver local routines    .                                                */
/*===========================================================================*/

#define PIXIL_POS(g, x, y)		((y) * ((fbPriv *)(g)->priv)->fbi.linelen + (x) * 3)
#define PIXEL_ADDR(g, pos)		(((gU8 *)((fbPriv *)(g)->priv)->fbi.pixels)+pos)

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

LLDSPEC gBool gdisp_lld_init(GDisplay *g) {

	// Initialize the private structure
	if (!(g->priv = gfxAlloc(sizeof(fbPriv))))
		gfxHalt("GDISP Fb24bpp: Failed to allocate private memory");
	((fbPriv *)g->priv)->fbi.pixels = 0;
	((fbPriv *)g->priv)->fbi.linelen = 0;

	// Initialize the GDISP structure
	g->g.Orientation = gOrientation0;
	g->g.Powermode = gPowerOn;
	g->board = 0;							// preinitialize
	board_init(g, &((fbPriv *)g->priv)->fbi);

	return gTrue;
}

#if GDISP_HARDWARE_FLUSH
	LLDSPEC void gdisp_lld_flush(GDisplay *g) {
		board_flush(g);
	}
#endif

LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g) {
	unsigned		pos;
	gU8			*p;

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

	p = PIXEL_ADDR(g, pos);
	
	#if GDISP_LLD_PIXELFORMAT == GDISP_PIXELFORMAT_RGB888
		p[0] = RED_OF(g->p.color);
		p[1] = GREEN_OF(g->p.color);
		p[2] = BLUE_OF(g->p.color);
	#else
		p[0] = BLUE_OF(g->p.color);
		p[1] = GREEN_OF(g->p.color);
		p[2] = RED_OF(g->p.color);
	#endif
}

LLDSPEC	gColor gdisp_lld_get_pixel_color(GDisplay *g) {
	unsigned		pos;
	gU8			*p;

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

	p = PIXEL_ADDR(g, pos);
	
	#if GDISP_LLD_PIXELFORMAT == GDISP_PIXELFORMAT_RGB888
		return RGB2COLOR(p[0], p[1], p[2]);
	#else
		return RGB2COLOR(p[2], p[1], p[0]);
	#endif
}

#if GDISP_NEED_CONTROL
	LLDSPEC void gdisp_lld_control(GDisplay *g) {
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
		}
	}
#endif

#endif /* GFX_USE_GDISP */
