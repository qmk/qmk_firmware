/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT			GDISPVMT_UC1610
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"

#include "board_UC1610.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#include "UC1610.h"

#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT		UC1610_SCREEN_HEIGHT
#endif

#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH		UC1610_SCREEN_WIDTH
#endif

#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST          40
#endif

#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT		100
#endif

// Some common routines and macros
#define PRIV(g)					((UC1610_Window *)g->priv)
#define RAM(g)					((gU8 *)(PRIV(g) + 1))
#define xyaddr(x, y)			((x) + GDISP_SCREEN_WIDTH * ((y) >> 2))
#define xybit(y, c)				((c) << (((y) & 3) << 1))
#define GDISP_FLG_NEEDFLUSH		(GDISP_FLG_DRIVER << 0)

typedef struct UC1610_Window {
	gCoord x1;
	gCoord y1;
	gCoord x2;
	gCoord y2;
} UC1610_Window;

/*===========================================================================*/
/* Driver local varriables.                                                  */
/*===========================================================================*/

static gU8 cmdBuffer[11];

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static void GFXINLINE power_on_sequence(GDisplay* g) {
	cmdBuffer[0]  = UC1610_SYSTEM_RESET;                 // software reset
	write_cmd(g, cmdBuffer, 1);
	gfxSleepMilliseconds(2);
	cmdBuffer[0]  = UC1610_SET_COM_END;                  // set com end value
	cmdBuffer[1]  = GDISP_SCREEN_HEIGHT - 1;
	cmdBuffer[2]  = UC1610_SET_PANEL_LOADING;
	cmdBuffer[3]  = UC1610_SET_LCD_BIAS_RATIO;
	cmdBuffer[4]  = UC1610_SET_VBIAS_POT;                // set contrast
	cmdBuffer[5]  = (gU8) (GDISP_INITIAL_CONTRAST * 254 / 100);
	cmdBuffer[6]  = UC1610_SET_MAPPING_CONTROL;          // bottom view
	cmdBuffer[7]  = UC1610_SET_SCROLL_LINES_LSB | 0;
	cmdBuffer[8]  = UC1610_SET_SCROLL_LINES_MSB | 0;     // set scroll line on line 0
	cmdBuffer[9]  = UC1610_SET_AC | UC1610_AC_WA_MASK;   // set auto increment wrap arround
	cmdBuffer[10] = UC1610_SET_DISPLAY_ENABLE | 1;       // turn display on
	write_cmd(g, cmdBuffer, 11);
}

static void GFXINLINE flush_screen(GDisplay* g) {
	PRIV(g)->x1 = 0;
	PRIV(g)->y1 = 0;
	PRIV(g)->x2 = GDISP_SCREEN_WIDTH-1;
	PRIV(g)->y2 = GDISP_SCREEN_HEIGHT-1;
	g->flags |= GDISP_FLG_NEEDFLUSH;
	gdisp_lld_flush(g);
}

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

LLDSPEC gBool gdisp_lld_init(GDisplay *g) {
	// The private area is the display surface + flush window structure.
	g->priv = gfxAlloc(sizeof(UC1610_Window) + GDISP_SCREEN_WIDTH * GDISP_SCREEN_HEIGHT / UC1610_PAGE_HEIGHT);

	// Clear the initial flush region
	PRIV(g)->x1 = GDISP_SCREEN_WIDTH;
	PRIV(g)->y1 = GDISP_SCREEN_HEIGHT;
	PRIV(g)->x2 = -1;
	PRIV(g)->y2 = -1;

	// Initialise the board interface
	init_board(g);

	// Hardware reset
        // not needed : reset pin set to ON by init_board(g), software reset by power_on_sequence(g)
	gfxSleepMilliseconds(12);

        // Acquire the bus
	acquire_bus(g);

	// Init commands sequence
	power_on_sequence(g);

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

#if GDISP_HARDWARE_DRAWPIXEL
	LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g) {
		gCoord x, y;
		gU8 *c;

		// handle orientation
		switch (g->g.Orientation) {
			default :
				x = g->p.x;
				y = g->p.y;
				break;
			case gOrientation90 :
				y = g->p.x;
				x = g->p.y;
				break;
			case gOrientation270 :
				y = g->p.x;
				x = g->p.y;
				break;
		}


		// update pixel color
		c = RAM(g) + xyaddr(x, y);
		*c &= ~xybit(y, LLDCOLOR_MASK());
		*c |= xybit(y, gdispColor2Native(g->p.color));

		// update flush window boundaries
		if (x < PRIV(g)->x1) { PRIV(g)->x1 = x; }
		if (x > PRIV(g)->x2) { PRIV(g)->x2 = x; }
		if (y < PRIV(g)->y1) { PRIV(g)->y1 = y; }
		if (y > PRIV(g)->y2) { PRIV(g)->y2 = y; }
		g->flags |= GDISP_FLG_NEEDFLUSH;
	}
#endif

#if GDISP_HARDWARE_FLUSH
	LLDSPEC void gdisp_lld_flush(GDisplay* g)
	{
		gCoord x1, y1, x2, y2, cx;
		gU8 *c;

		// Don't flush unless we really need to
		if (!(g->flags & GDISP_FLG_NEEDFLUSH))
			return;

		x1 = PRIV(g)->x1;
		y1 = PRIV(g)->y1;
		x2 = PRIV(g)->x2;
		y2 = PRIV(g)->y2;
		cx = x2 - x1 + 1;

		// Clear the 'need-flushing' flag and reset the window
		g->flags &= ~GDISP_FLG_NEEDFLUSH;
		PRIV(g)->x1 = GDISP_SCREEN_WIDTH;
		PRIV(g)->y1 = GDISP_SCREEN_HEIGHT;
		PRIV(g)->x2 = -1;
		PRIV(g)->y2 = -1;

		// set window to fill
		cmdBuffer[0] = UC1610_SET_WINDOW_PROGRAM_ENABLE | 0;	// before changing boundaries
		cmdBuffer[1] = UC1610_SET_WP_STARTING_CA;
		cmdBuffer[2] = x1;
		cmdBuffer[3] = UC1610_SET_WP_ENDING_CA;
		cmdBuffer[4] = x2;
		cmdBuffer[5] = UC1610_SET_WP_STARTING_PA;
		cmdBuffer[6] = y1 >> 2;
		cmdBuffer[7] = UC1610_SET_WP_ENDING_PA;
		cmdBuffer[8] = y2 >> 2;
		cmdBuffer[9] = UC1610_SET_WINDOW_PROGRAM_ENABLE | 1;	// entering window programming

		acquire_bus(g);
		write_cmd (g, cmdBuffer, 10);

		// write each page segment from RAM(g) to display RAM
		for (c = RAM(g) + xyaddr(x1, y1) ; y1 <= y2 ; c += GDISP_SCREEN_WIDTH, y1 += UC1610_PAGE_HEIGHT) {
			write_data(g, c, cx);
		}
		release_bus(g);
	}
#endif

#if GDISP_NEED_CONTROL && GDISP_HARDWARE_CONTROL
	LLDSPEC void gdisp_lld_control(GDisplay *g) {
		switch(g->p.x) {
			case GDISP_CONTROL_POWER:
				if (g->g.Powermode == (gPowermode)g->p.ptr) { return; }
				switch((gPowermode)g->p.ptr) {
					case gPowerOff:
						cmdBuffer[0] = UC1610_SYSTEM_RESET;
						acquire_bus(g);
						write_cmd(g, cmdBuffer, 1);
						release_bus(g);
						gfxSleepMilliseconds(2);
						break;
					case gPowerSleep:
						cmdBuffer[0] = UC1610_SET_DISPLAY_ENABLE | 0;
						acquire_bus(g);
						write_cmd(g, cmdBuffer, 1);
						release_bus(g);
						gfxSleepMilliseconds(2);
						break;
					case gPowerOn:
						if (g->g.Powermode == gPowerSleep) {
							cmdBuffer[0] = UC1610_SET_DISPLAY_ENABLE | 1;
							acquire_bus(g);
							write_cmd(g, cmdBuffer, 1);
							release_bus(g);
							flush_screen(g);
						} else {
							gfxSleepMilliseconds(12);
							acquire_bus(g);
							power_on_sequence(g);
							release_bus(g);
						}
						break;
					default:
						return;
				}
				g->g.Powermode = (gPowermode)g->p.ptr;
				return;

			case GDISP_CONTROL_ORIENTATION:
				if (g->g.Orientation == (gOrientation)g->p.ptr) { return; }
				switch((gOrientation)g->p.ptr) {
					case gOrientation0:
						g->g.Width  = GDISP_SCREEN_WIDTH;
						g->g.Height = GDISP_SCREEN_HEIGHT;
						cmdBuffer[0] = UC1610_SET_MAPPING_CONTROL;
						acquire_bus(g);
						write_cmd(g, cmdBuffer, 1);
						release_bus(g);
						flush_screen(g);
						break;
					case gOrientation180:	// we can rotate 180° without modify screen buffer RAM(g)
						g->g.Width  = GDISP_SCREEN_WIDTH;
						g->g.Height = GDISP_SCREEN_HEIGHT;
						cmdBuffer[0] = UC1610_SET_MAPPING_CONTROL | UC1610_SET_MAPPING_CONTROL_MY_MASK | UC1610_SET_MAPPING_CONTROL_MX_MASK;
						acquire_bus(g);
						write_cmd(g, cmdBuffer, 1);
						release_bus(g);
						flush_screen(g);
						break;
					case gOrientation90:	// needs clearing screen and updating RAM(g)
						g->g.Width  = GDISP_SCREEN_HEIGHT;
						g->g.Height = GDISP_SCREEN_WIDTH;
						cmdBuffer[0] = UC1610_SET_MAPPING_CONTROL | UC1610_SET_MAPPING_CONTROL_MX_MASK;
						acquire_bus(g);
						write_cmd(g, cmdBuffer, 1);
						release_bus(g);
						break;
					case gOrientation270:	// needs clearing screen and updating RAM(g)
						g->g.Width  = GDISP_SCREEN_HEIGHT;
						g->g.Height = GDISP_SCREEN_WIDTH;
						cmdBuffer[0] = UC1610_SET_MAPPING_CONTROL | UC1610_SET_MAPPING_CONTROL_MY_MASK;
						acquire_bus(g);
						write_cmd(g, cmdBuffer, 1);
						release_bus(g);
						break;
					default:
						return;
				}
				g->g.Orientation = (gOrientation)g->p.ptr;
				return;

			case GDISP_CONTROL_BACKLIGHT:
				// TODO: backlight support at board level
				/*if ((unsigned)g->p.ptr > 100) { g->p.ptr = (void *)100; }
				set_backlight(g, (unsigned)g->p.ptr);
				g->g.Backlight = (unsigned)g->p.ptr;*/
				return;

			case GDISP_CONTROL_CONTRAST:
				if ((unsigned)g->p.ptr > 100) { g->p.ptr = (void *)100; }
				acquire_bus(g);
				cmdBuffer[0] = UC1610_SET_VBIAS_POT;
				cmdBuffer[1] = (gU8)((unsigned)g->p.ptr * 254 / 100);
				write_cmd(g, cmdBuffer, 2);
				release_bus(g);
				g->g.Contrast = (unsigned)g->p.ptr;
				flush_screen(g);
				return;

			case GDISP_CONTROL_INVERSE:
				cmdBuffer[0] = g->p.ptr ? (UC1610_SET_INVERSE_DISPLAY | 1) : (UC1610_SET_INVERSE_DISPLAY | 0);
				acquire_bus(g);
				write_cmd(g, cmdBuffer, 1);
				release_bus(g);
				//flush_screen(g);
				return;
		}
	}
#endif

#endif // GFX_USE_GDISP
