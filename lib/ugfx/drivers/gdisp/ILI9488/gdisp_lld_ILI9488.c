/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "gfx.h"

#if GFX_USE_GDISP

#if defined(GDISP_SCREEN_HEIGHT) || defined(GDISP_SCREEN_HEIGHT)
	#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
		#warning "GDISP: This low level driver does not support setting a screen size. It is being ignored."
	#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
		COMPILER_WARNING("GDISP: This low level driver does not support setting a screen size. It is being ignored.")
	#endif
	#undef GDISP_SCREEN_WIDTH
	#undef GDISP_SCREEN_HEIGHT
#endif

#define GDISP_DRIVER_VMT			GDISPVMT_ILI9488
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"

#include "board_ILI9488.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT		480
#endif
#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH		320
#endif
#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	50
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/
static void dummy_read(GDisplay* g) {
  volatile gU16 dummy;
  dummy = read_data(g);
  (void)dummy;
}

static void set_viewport(GDisplay* g) {
  write_index(g, 0x2A);
  write_data(g, ((g->p.x >> 8) & 0x00FF));
  write_data(g, ((g->p.x >> 0) & 0x00FF));
  write_data(g, ((g->p.x + g->p.cx - 1) >> 8) & 0x00FF);
  write_data(g, ((g->p.x + g->p.cx - 1) >> 0) & 0x00FF);

  write_index(g, 0x2B);
  write_data(g, ((g->p.y >> 8) & 0x00FF));
  write_data(g, ((g->p.y >> 0) & 0x00FF));
  write_data(g, ((g->p.y + g->p.cy - 1) >> 8) & 0x00FF);
  write_data(g, ((g->p.y + g->p.cy - 1) >> 0) & 0x00FF);

	write_index(g, 0x2C);
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

LLDSPEC gBool gdisp_lld_init(GDisplay *g) {
	// No private area for this controller
	g->priv = 0;

	// Initialise the board interface
	init_board(g);

	/* Hardware reset */
	setpin_reset(g, gTrue);
	gfxSleepMilliseconds(2);
  setpin_reset(g, gFalse);
  gfxSleepMilliseconds(10);
  setpin_reset(g, gTrue);
  gfxSleepMilliseconds(120);

	/* Get the bus for the following initialisation commands */
	acquire_bus(g);

	write_index(g, 0xF7);
	write_data(g, 0xA9);
	write_data(g, 0x51);
	write_data(g, 0x2C);
	write_data(g, 0x82);

	write_index(g, 0xC0);
	write_data(g, 0x11);
	write_data(g, 0x09);

	write_index(g, 0xC1);
	write_data(g, 0x41);

	write_index(g, 0xC5);
	write_data(g, 0x00);
	write_data(g, 0x2A);
	write_data(g, 0x80);

	write_index(g, 0xB1);
	write_data(g, 0xB0);
	write_data(g, 0x11);

	write_index(g, 0xB4);
	write_data(g, 0x02);

	write_index(g, 0xB6);
	write_data(g, 0x02);
	write_data(g, 0x22);
	write_data(g, 0x3B);

	write_index(g, 0xB7);
	write_data(g, 0xC6);

	write_index(g, 0xBE);
	write_data(g, 0x00);
	write_data(g, 0x04);

	write_index(g, 0xE9);
	write_data(g, 0x00);

	write_index(g, 0x36);
	write_data(g, 0x08);

	write_index(g, 0x3A);
	write_data(g, 0x55);

	write_index(g, 0xE0);
	write_data(g, 0x00);
	write_data(g, 0x07);
	write_data(g, 0x12);
	write_data(g, 0x0B);
	write_data(g, 0x18);
	write_data(g, 0x0B);
	write_data(g, 0x3F);
	write_data(g, 0x9B);
	write_data(g, 0x4B);
	write_data(g, 0x0B);
	write_data(g, 0x0F);
	write_data(g, 0x0B);
	write_data(g, 0x15);
	write_data(g, 0x17);
	write_data(g, 0x0F);

	write_index(g, 0xE1);
	write_data(g, 0x00);
	write_data(g, 0x16);
	write_data(g, 0x1B);
	write_data(g, 0x02);
	write_data(g, 0x0F);
	write_data(g, 0x06);
	write_data(g, 0x34);
	write_data(g, 0x46);
	write_data(g, 0x48);
	write_data(g, 0x04);
	write_data(g, 0x0D);
	write_data(g, 0x0D);
	write_data(g, 0x35);
	write_data(g, 0x36);
	write_data(g, 0x0F);

	write_index(g, 0x11);
	gfxSleepMilliseconds(120);
	write_index(g, 0x29);

  // Finish Init
  post_init_board(g);

 	// Release the bus
	release_bus(g);
	
	// Turn on the back-light
	set_backlight(g, GDISP_INITIAL_BACKLIGHT);

	// Initialise the GDISP structure
	g->g.Width = GDISP_SCREEN_WIDTH;
	g->g.Height = GDISP_SCREEN_HEIGHT;
	g->g.Orientation = gOrientation0;
	g->g.Powermode = gPowerOn;
	g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
	g->g.Contrast = GDISP_INITIAL_CONTRAST;

	return gTrue;
}

#if GDISP_HARDWARE_STREAM_WRITE
	LLDSPEC	void gdisp_lld_write_start(GDisplay *g) {
		acquire_bus(g);
		set_viewport(g);
	}

	LLDSPEC	void gdisp_lld_write_color(GDisplay *g) {
		write_data(g, gdispColor2Native(g->p.color));
	}

	LLDSPEC	void gdisp_lld_write_stop(GDisplay *g) {
		release_bus(g);
	}
#endif

#if GDISP_HARDWARE_STREAM_READ
	LLDSPEC	void gdisp_lld_read_start(GDisplay *g) {
		acquire_bus(g);
		set_viewport(g);
		setreadmode(g);
		dummy_read(g);
	}

	LLDSPEC	gColor gdisp_lld_read_color(GDisplay *g) {
		gU16	data;

		data = read_data(g);
		return gdispNative2Color(data);
	}

	LLDSPEC	void gdisp_lld_read_stop(GDisplay *g) {
		setwritemode(g);
		release_bus(g);
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
