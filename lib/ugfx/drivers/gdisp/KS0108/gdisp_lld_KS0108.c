/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "gfx.h"

#if GFX_USE_GDISP

/* Robert Offner 2017
 * This is a driver for the KS0107 Displays.
 * It should work with displays up to 240 pixel in width and 64 pixel in height
 * ATTENTION some newer displays on ebay look like KS0107 Type but they're not!
 * They use a new controller: ST7920. These are easy to identify: NO CS pin but
 * a PSB Pin which switches from parallel to serial communication mode.
 * If it cost less than 10.- it is probably a ST7920.
 * Features: Well not much. For now write pixel to display and
 * Read from Display / Buffer in RAM. Buffer in Ram is much faster than
 * readback!
 * I am trying to get the auto increment feature somehow implemented. It
 * basically means if you start at x=0 and continue with x=1, x=2,... you don't
 * have to write the address just data.
 *
 * Version: 0.3
 *
 * History:
 * v0.4
 * .) Cleanup by uGFX team. Code needs a lot of work.
 *
 * v0.3
 * .) Removed initialization of g->priv because it is already done by uGFX.
 *
 * v0.2
 * .) Cleanup,
 * .) changed osalThreadSleep to gfxSleepMicroseconds(x)
 *    ATTENTION: for gfxSleepMicroseconds to work on chibios you have to
 *    increase CH_CFG_ST_FREQUENCY to 1000000 and probably CH_CFG_ST_RESOLUTION
 *    to 32 bit (not tested because STM32F103 doesn't have a 32 bit timer
 * .) changed lcdbuf to g->priv
 *
 * v0.1 Initial Release
 */

#define GDISP_DRIVER_VMT			GDISPVMT_KS0108
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"

#include "board_KS0108.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT		64
#endif
#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH		128
#endif

#define CHIPS (GDISP_SCREEN_WIDTH/64)

#if !KS0108_NEED_READ
	#define BUFFSZ (GDISP_SCREEN_HEIGHT/8 * GDISP_SCREEN_WIDTH)
	#define RAM(g) ((gU8 *)g->priv)
#endif
#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	50
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif

// KS0108 Commands
#define KS0108_CHIP1_ON                0x003F
#define KS0108_CHIP2_ON                0x013F
#define KS0108_DISP1START              0x00C0
#define KS0108_DISP2START              0x01C0
#define KS0108_DISP1OFF                0x003E
#define KS0108_DISP2OFF                0x013E
#define KS0108_SET_ADDR                0x0040
#define KS0108_SET_PAGE                0x00B8

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/
#ifndef write_data_repeat
	#define write_data_repeat(g, data, count) { int i; for (i = 0; i < count; ++i) write_data (g, data); }
#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

LLDSPEC gBool gdisp_lld_init(GDisplay *g) {
	#if !KS0108_NEED_READ
		// The private area is the display surface.
		g->priv = gfxAlloc(BUFFSZ);
	#else
		g->priv = 0;
	#endif
	// Initialise the board interface
	init_board(g);

	#if KS0108_HAS_RESET  //Make Hardware Reset
		setpin_reset(g, gTrue);
		gfxSleepMilliseconds(120);
		setpin_reset(g, gFalse);
	#endif
	gfxSleepMilliseconds(120);
	write_cmd(g, KS0108_DISP1OFF);
	gfxSleepMilliseconds(1);
	write_cmd(g, KS0108_DISP2OFF);
	gfxSleepMilliseconds(1);
	write_cmd(g, KS0108_CHIP1_ON);                        //0x3F Chip1
	gfxSleepMilliseconds(1);
	write_cmd(g, KS0108_CHIP2_ON);                        //0x3F Chip2
	gfxSleepMilliseconds(1);
	write_cmd(g, KS0108_DISP1START);                      //0xC0 Chip1
	gfxSleepMilliseconds(1);
	write_cmd(g, KS0108_DISP2START);                      //0xC0 Chip2
	gfxSleepMilliseconds(1);

	// Finish Init
	post_init_board(g);

	#if KS0108_NEED_BACKLIGHT
		// Turn on the back-light
		set_backlight(g, GDISP_INITIAL_BACKLIGHT);
	#endif

	// Initialise the GDISP structure
	g->g.Width = GDISP_SCREEN_WIDTH;
	g->g.Height = GDISP_SCREEN_HEIGHT;
	g->g.Orientation = gOrientation0;
	g->g.Powermode = gPowerOn;
	g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
	g->g.Contrast = GDISP_INITIAL_CONTRAST;

	return gTrue;
}

GFXINLINE void KS0108_goto(GDisplay* g, ) {
}

static void set_viewport(GDisplay *g) {
	gU16	pg;
	gU16	chip;
	
	pg = g->p.y >> 3;
	chip = (g->p.x >> 6) << 8;
	write_cmd(g, KS0108_SET_PAGE | chip | pg);			// (0xB8) - Set page
	write_cmd(g, KS0108_SET_ADDR | chip | g->p.x);		// (0x40) - Set x Address
}

LLDSPEC void gdisp_lld_write_color(GDisplay *g) {
	gU16	data;

	data = (g->p.x >> 6) << 8;		// Set the chip
	if (g->p.color != GFX_WHITE)
		data |= 0x01;				// set dot
	write_data(g, data);
}

LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g) {
	set_viewport(g);
	gdisp_lld_write_color(g);
}

#if GDISP_HARDWARE_STREAM_WRITE
	LLDSPEC void gdisp_lld_write_start(GDisplay *g) {
		acquire_bus(g);
		set_viewport(g);
	}

	LLDSPEC void gdisp_lld_write_stop(GDisplay *g) {
		release_bus(g);
	}
#endif

#if GDISP_HARDWARE_STREAM_READ
	LLDSPEC void gdisp_lld_read_start(GDisplay *g) {
		acquire_bus(g);
		set_viewport(g);
		setreadmode(g);
		dummy_read(g);
	}

	LLDSPEC gColor gdisp_lld_read_color(GDisplay *g) {
		gU16 data;

		data = read_data(g);
		return gdispNative2Color(data);
	}

	LLDSPEC void gdisp_lld_read_stop(GDisplay *g) {
		setwritemode(g);
		release_bus(g);
	}
#endif

#if GDISP_HARDWARE_FILLS
	LLDSPEC void gdisp_lld_fill_area(GDisplay *g) {
		gU8 data, j;
		set_viewport(g);

		if (g->p.color != GFX_WHITE) {
			data = 0xFF;              // set dot
		}
		else {
			data = 0;              // clr dot
		}
		for (j=0; j < (g->p.cy)/8; j++) {
			write_data_repeat(g, data, (g->p.cx));
			(g->p.cy) +=8;
			set_viewport(g);
		}

	}
#endif // GDISP_HARDWARE_FILLS

#if GDISP_NEED_CONTROL && GDISP_HARDWARE_CONTROL
	LLDSPEC void gdisp_lld_control(GDisplay *g) {
		switch(g->p.x) {
		case GDISP_CONTROL_POWER:
			if (g->g.Powermode == (gPowermode)g->p.ptr)
				return;

			switch((gPowermode)g->p.ptr) {
			case gPowerOff:
				acquire_bus(g);
				write_index(g, 0x28);
				gfxSleepMilliseconds(10);
				write_index(g, 0x10);
				release_bus(g);
				break;

			case gPowerOn:
				acquire_bus(g);
				write_index(g, 0x11);
				gfxSleepMilliseconds(120);
				write_index(g, 0x29);
				release_bus(g);
				if (g->g.Powermode != gPowerSleep)
					gdisp_lld_init(g);
			break;

			case gPowerSleep:
				acquire_bus(g);
				write_index(g, 0x28);
				gfxSleepMilliseconds(10);
				write_index(g, 0x10);
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
				acquire_bus(g);

				write_index(g, 0x36);
				write_data(g, 0x08);

				release_bus(g);
				g->g.Height = GDISP_SCREEN_HEIGHT;
				g->g.Width = GDISP_SCREEN_WIDTH;
				break;

			case gOrientation90:
				acquire_bus(g);

				write_index(g, 0x36);
				write_data(g, 0x68);

				release_bus(g);
				g->g.Height = GDISP_SCREEN_WIDTH;
				g->g.Width = GDISP_SCREEN_HEIGHT;
				break;

			case gOrientation180:
				acquire_bus(g);

				write_index(g, 0x36);
				write_data(g, 0xC8);

				release_bus(g);
				g->g.Height = GDISP_SCREEN_HEIGHT;
				g->g.Width = GDISP_SCREEN_WIDTH;
				break;

			case gOrientation270:
				acquire_bus(g);

				write_index(g, 0x36);
				write_data(g, 0xA8);

				release_bus(g);
				g->g.Height = GDISP_SCREEN_WIDTH;
				g->g.Width = GDISP_SCREEN_HEIGHT;
				break;

			default:
				return;
			}

			g->g.Orientation = (gOrientation)g->p.ptr;
			return;

		default:
			return;
		}
	}
#endif

#endif /* GFX_USE_GDISP */
