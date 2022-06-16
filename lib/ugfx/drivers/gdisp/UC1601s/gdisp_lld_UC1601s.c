/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              https://ugfx.io/license.html
 *
 * Author: pashamray
 * e-mail: pashamray@gmail.com
 * github: https://github.com/pashamray
 * 
 * this driver based on code: 
 *    http://caxapa.ru/thumbs/316734/rdx0154gc.zip
 *    http://leoniv.livejournal.com/124005.html
 *    Author: leoniv
 *    Web site: http://leoniv.livejournal.com
 *
 */

#include "gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT			GDISPVMT_UC1601s
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"

#include "board_UC1601s.h"
#include <string.h>   // for memset

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT     64
#endif
#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH      132
#endif
#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST  47
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT 100
#endif

#define GDISP_FLG_NEEDFLUSH         (GDISP_FLG_DRIVER << 0)

#include "UC1601s.h"

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

// Some common routines and macros
#define RAM(g)                      		((gU8 *)g->priv)

#define xyaddr(x, y)		        		((x) + ((y) >> 3) * GDISP_SCREEN_WIDTH)
#define xybit(y)			        		(1 << ((y) & 7))

/**
 * As this controller can't update on a pixel boundary we need to maintain the
 * the entire display surface in memory so that we can do the necessary bit
 * operations. Fortunately it is a small display in monochrome.
 * 64 * 132 / 8 = 1056 bytes.
 */
#define GDISP_SCREEN_BYTES          ((GDISP_SCREEN_WIDTH * GDISP_SCREEN_HEIGHT) / 8)
#define GDISP_SCREEN_PAGE_SIZE		8
#define GDISP_SCREEN_PAGES			GDISP_SCREEN_HEIGHT / GDISP_SCREEN_PAGE_SIZE
/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

LLDSPEC gBool gdisp_lld_init(GDisplay *g) {
    
	// The private area is the display surface.
	if (!(g->priv = gfxAlloc(GDISP_SCREEN_BYTES)))
    {
		gfxHalt("GDISP UC1601s: Failed to allocate private memory");
    }
    
    memset(RAM(g), 0, GDISP_SCREEN_BYTES);

	// Initialise the board interface
	init_board(g);

	// Hardware reset
	setpin_reset(g, gTrue);
	gfxSleepMilliseconds(5);
	setpin_reset(g, gFalse);

	acquire_bus(g);

	write_cmd(g, UC1601s_RESET);

    gfxSleepMilliseconds(10);
    write_cmd2(g, UC1601s_SET_BIAS, (gU8)(((GDISP_INITIAL_CONTRAST << 8) - 1) / 100));
    
    write_cmd(g, UC1601s_SET_EN | UC1601s_ENABLE);

    // Finish Init
    post_init_board(g);

 	// Release the bus
	release_bus(g);

	/* Initialise the GDISP structure */
	g->g.Width = GDISP_SCREEN_WIDTH;
	g->g.Height = GDISP_SCREEN_HEIGHT;
	g->g.Orientation = gOrientation0;
	g->g.Powermode = gPowerOn;
	g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
	g->g.Contrast = GDISP_INITIAL_CONTRAST;
	return gTrue;
}

#if GDISP_HARDWARE_FLUSH
	LLDSPEC void gdisp_lld_flush(GDisplay *g) {

		// Don't flush if we don't need it.
		if (!(g->flags & GDISP_FLG_NEEDFLUSH)) {
			return;
		}

		acquire_bus(g);

		for (int i = 0; i < GDISP_SCREEN_PAGES; ++i)
		{
   			write_cmd3(g, UC1601s_SET_PAGE | i, UC1601s_SET_COL_L | (0 & 0x0f), UC1601s_SET_COL_H | ((0 >> 4) & 0x0f)); // Y, XL, XH
			write_data(g, RAM(g) + (i * GDISP_SCREEN_WIDTH), GDISP_SCREEN_WIDTH);
		}

		release_bus(g);

		g->flags &= ~GDISP_FLG_NEEDFLUSH;
	}
#endif

#if GDISP_HARDWARE_DRAWPIXEL
	LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g) {
		gCoord x, y;
		
		#if GDISP_NEED_CONTROL
			switch(g->g.Orientation) {
			default:
			case gOrientation0:
				x = g->p.x;
				y = g->p.y;
				break;
			case gOrientation90:
				x = g->p.y;
				y = g->g.Width - g->p.x - 1;
				break;
			case gOrientation180:
				x = g->g.Width  - g->p.x - 1;
				y = g->g.Height - g->p.y - 1;
				break;
			case gOrientation270:
				x = g->g.Height - g->p.y - 1;
				y = g->p.x;
				break;
			}
		#else
			x = g->p.x;
			y = g->p.y;
		#endif

		if (gdispColor2Native(g->p.color) != GFX_BLACK) {
			RAM(g)[xyaddr(x, y)] |= xybit(y);
		} else {
			RAM(g)[xyaddr(x, y)] &= ~xybit(y);
		}

		g->flags |= GDISP_FLG_NEEDFLUSH;
	}
#endif

#if GDISP_HARDWARE_PIXELREAD
	LLDSPEC gColor gdisp_lld_get_pixel_color(GDisplay *g) {
		gCoord		x, y;

		switch(g->g.Orientation) {
		default:
		case gOrientation0:
			x = g->p.x;
			y = g->p.y;
			break;
		case gOrientation90:
			x = g->p.y;
			y = GDISP_SCREEN_HEIGHT-1 - g->p.x;
			break;
		case gOrientation180:
			x = GDISP_SCREEN_WIDTH-1 - g->p.x;
			y = GDISP_SCREEN_HEIGHT-1 - g->p.y;
			break;
		case gOrientation270:
			x = GDISP_SCREEN_WIDTH-1 - g->p.y;
			y = g->p.x;
			break;
		}
		return (RAM(g)[xyaddr(x, y)] & xybit(y)) ? GFX_WHITE : GFX_BLACK;
	}
#endif

#if GDISP_NEED_CONTROL && GDISP_HARDWARE_CONTROL
	LLDSPEC void gdisp_lld_control(GDisplay *g) {
		switch(g->p.x) {
		case GDISP_CONTROL_POWER:
			if (g->g.Powermode == (gPowermode)g->p.ptr)
				return;
			switch((gPowermode)g->p.ptr) {
				case gPowerOff:
				case gPowerSleep:
				case gPowerDeepSleep:
					acquire_bus(g);
					write_cmd(g, UC1601s_SET_EN);
					release_bus(g);
					break;
				case gPowerOn:
					acquire_bus(g);
					write_cmd(g, UC1601s_SET_EN | UC1601s_ENABLE);
					release_bus(g);
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
			set_backlight(g, (unsigned)g->p.ptr);
			g->g.Backlight = (unsigned)g->p.ptr;
			return;

		case GDISP_CONTROL_CONTRAST:
			if ((unsigned)g->p.ptr > 100) g->p.ptr = (void *)100;
			acquire_bus(g);
			write_cmd2(g, UC1601s_SET_BIAS, (gU8)(((((unsigned)g->p.ptr) << 8) - 1) / 100));
			release_bus(g);
			g->g.Contrast = (unsigned)g->p.ptr;
			return;
		}
	}
#endif

#if GDISP_HARDWARE_FILLS
	LLDSPEC void gdisp_lld_fill_area(GDisplay *g) {
		g->flags |= GDISP_FLG_NEEDFLUSH;
	}
#endif

#endif // GFX_USE_GDISP
