/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT			GDISPVMT_ST7565
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"

#include "board_ST7565.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT		64
#endif
#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH		128
#endif
#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	51
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif

#define GDISP_FLG_NEEDFLUSH			(GDISP_FLG_DRIVER<<0)

#include "st7565.h"

/*===========================================================================*/
/* Driver config defaults for backward compatibility.               	     */
/*===========================================================================*/
#ifndef ST7565_LCD_BIAS
  #define ST7565_LCD_BIAS         ST7565_LCD_BIAS_7
#endif
#ifndef ST7565_ADC
  #define ST7565_ADC              ST7565_ADC_NORMAL
#endif
#ifndef ST7565_COM_SCAN
  #define ST7565_COM_SCAN         ST7565_COM_SCAN_INC
#endif
#ifndef ST7565_PAGE_ORDER
  #define ST7565_PAGE_ORDER       0,1,2,3,4,5,6,7
#endif

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

// Some common routines and macros
#define RAM(g)							((gU8 *)g->priv)
#define write_cmd2(g, cmd1, cmd2)		{ write_cmd(g, cmd1); write_cmd(g, cmd2); }
#define write_cmd3(g, cmd1, cmd2, cmd3)	{ write_cmd(g, cmd1); write_cmd(g, cmd2); write_cmd(g, cmd3); }

// Some common routines and macros
#define delay(us)			gfxSleepMicroseconds(us)
#define delay_ms(ms)		gfxSleepMilliseconds(ms)

#define xyaddr(x, y)		((x) + ((y)>>3)*GDISP_SCREEN_WIDTH)
#define xybit(y)			(1<<((y)&7))

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/*
 * As this controller can't update on a pixel boundary we need to maintain the
 * the entire display surface in memory so that we can do the necessary bit
 * operations. Fortunately it is a small display in monochrome.
 * 64 * 128 / 8 = 1024 bytes.
 */

LLDSPEC gBool gdisp_lld_init(GDisplay *g) {
	// The private area is the display surface.
	g->priv = gfxAlloc(GDISP_SCREEN_HEIGHT * GDISP_SCREEN_WIDTH / 8);
	if (!g->priv) {
		return gFalse;
	}

	// Initialise the board interface
	init_board(g);

	// Hardware reset
	setpin_reset(g, gTrue);
	gfxSleepMilliseconds(20);
	setpin_reset(g, gFalse);
	gfxSleepMilliseconds(20);

	acquire_bus(g);

    write_cmd(g, ST7565_LCD_BIAS);
    write_cmd(g, ST7565_ADC);
    write_cmd(g, ST7565_COM_SCAN);

	write_cmd(g, ST7565_START_LINE | 0);

	write_cmd2(g, ST7565_CONTRAST, GDISP_INITIAL_CONTRAST*64/101);
	write_cmd(g, ST7565_RESISTOR_RATIO | 0x3);

	// turn on voltage converter (VC=1, VR=0, VF=0)
	write_cmd(g, ST7565_POWER_CONTROL | 0x04);
	delay_ms(50);

	// turn on voltage regulator (VC=1, VR=1, VF=0)
	write_cmd(g, ST7565_POWER_CONTROL | 0x06);
	delay_ms(50);

	// turn on voltage follower (VC=1, VR=1, VF=1)
	write_cmd(g, ST7565_POWER_CONTROL | 0x07);
	delay_ms(50);

	write_cmd(g, ST7565_DISPLAY_ON);
	write_cmd(g, ST7565_ALLON_NORMAL);
	write_cmd(g, ST7565_POSITIVE_DISPLAY);	// Disable Inversion of display.

	write_cmd(g, ST7565_RMW);

    // Finish Init
    post_init_board(g);

 	// Release the bus
	release_bus(g);

	// Initialise the GDISP structure
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
		unsigned	p;

		// Don't flush if we don't need it.
		if (!(g->flags & GDISP_FLG_NEEDFLUSH))
			return;

		acquire_bus(g);
		gU8 pagemap[8]={ST7565_PAGE_ORDER};
		for (p = 0; p < 8; p++) {
			write_cmd(g, ST7565_PAGE | pagemap[p]);
			write_cmd(g, ST7565_COLUMN_MSB | 0);
			write_cmd(g, ST7565_COLUMN_LSB | 0);
			write_cmd(g, ST7565_RMW);
			write_data(g, RAM(g) + (p*GDISP_SCREEN_WIDTH), GDISP_SCREEN_WIDTH);
		}
		release_bus(g);

		g->flags &= ~GDISP_FLG_NEEDFLUSH;
	}
#endif

#if GDISP_HARDWARE_DRAWPIXEL
	LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g) {
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
			x = GDISP_SCREEN_HEIGHT-1 - g->p.y;
			y = g->p.x;
			break;
		}
		if (gdispColor2Native(g->p.color) != GFX_BLACK)
			RAM(g)[xyaddr(x, y)] |= xybit(y);
		else
			RAM(g)[xyaddr(x, y)] &= ~xybit(y);
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
			x = GDISP_SCREEN_HEIGHT-1 - g->p.y;
			x = g->p.x;
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
				write_cmd(g, ST7565_DISPLAY_OFF);
				release_bus(g);
				break;
			case gPowerOn:
				acquire_bus(g);
				write_cmd(g, ST7565_DISPLAY_ON);
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
			// Rotation is handled by the drawing routines
			case gOrientation0:
			case gOrientation180:
				g->g.Height = GDISP_SCREEN_HEIGHT;
				g->g.Width = GDISP_SCREEN_WIDTH;
				break;
			case gOrientation90:
			case gOrientation270:
				g->g.Height = GDISP_SCREEN_WIDTH;
				g->g.Width = GDISP_SCREEN_HEIGHT;
				break;
			default:
				return;
			}
			g->g.Orientation = (gOrientation)g->p.ptr;
			return;

		case GDISP_CONTROL_CONTRAST:
            if ((unsigned)g->p.ptr > 100)
            	g->p.ptr = (void *)100;
			acquire_bus(g);
			write_cmd2(g, ST7565_CONTRAST, ((((unsigned)g->p.ptr)<<6)/101) & 0x3F);
			release_bus(g);
            g->g.Contrast = (unsigned)g->p.ptr;
			return;
		}
	}
#endif // GDISP_NEED_CONTROL

#endif // GFX_USE_GDISP
