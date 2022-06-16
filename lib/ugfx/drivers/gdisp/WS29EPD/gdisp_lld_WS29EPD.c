/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT			GDISPVMT_WS29EPD
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"

#include "board_WS29EPD.h"
#include "WS29EPD.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT		296
#endif
#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH		128
#endif

/* Every data byte determines 8 pixels. */
#ifndef WS29EPD_PPB
  #define WS29EPD_PPB   8
#endif

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/* initialization variables according to WaveShare. */
gU8 GDOControl[]        = {(GDISP_SCREEN_HEIGHT-1)%256,(GDISP_SCREEN_HEIGHT-1)/256,0x00};
gU8 softstart[]         = {0xd7,0xd6,0x9d};
gU8 LUTDefault_full[]    = {0x02,0x02,0x01,0x11,0x12,0x12,0x22,0x22,0x66,0x69,0x69,0x59,0x58,0x99,0x99,0x88,0x00,0x00,0x00,0x00,0xF8,0xB4,0x13,0x51,0x35,0x51,0x51,0x19,0x01,0x00}; // Initialize the full display

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

LLDSPEC gBool gdisp_lld_init(GDisplay *g) {
	/* Use the private area as a frame buffer.
	*
	* The frame buffer will be one big array of bytes storing all the pixels with WS29EPD_PPB pixel per byte.
	* For the layout, the frame will be stored line by line in the x-direction.
	* So: [Line x=0][Line x=1][Line x=2] ... [Line x=GDISP_SCREEN_WIDTH/WS29EPD_PPB]
	* And every x-line contains GDISP_SCREEN_HEIGHT y-values:
	* [y=0; y=1; y=2; y=3; ...; y=GDISP_SCREEN_HEIGHT][y=0; y=1; y=2; y=3; ...; y=GDISP_SCREEN_HEIGHT]...
	*
	*/
	g->priv = gfxAlloc((GDISP_SCREEN_WIDTH / WS29EPD_PPB) * GDISP_SCREEN_HEIGHT * sizeof(gU8));
	if (!g->priv)
		return gFalse;

	/* Initialize the LL hardware. */
	init_board(g);

	/* Hardware reset. */
	setpin_reset(g, gFalse);
	gfxSleepMilliseconds(100);
	setpin_reset(g, gTrue);
	gfxSleepMilliseconds(100);

	/* Acquire the bus for the whole initialization. */
	acquire_bus(g);

	/* Send the initialization commands. (according to WaveShare) */
	write_reg_data(g, DRIVER_OUTPUT_CTRL, GDOControl, sizeof(GDOControl)/sizeof(GDOControl[0]));
	write_reg_data(g, BOOSTER_SOFT_START_CTRL, softstart, sizeof(softstart)/sizeof(softstart[0]));
	write_reg(g, WRITE_VCOM_REG, 0xA8);           // VCOM 7c
	write_reg(g, SET_DUMMY_LINE_PERIOD, 0x1A);    // 4 dummy lines per gate
	write_reg(g, SET_GATE_LINE_WIDTH, 0x08);      // 2us per line -> Lower this value for faster screen refresh
	write_reg(g, DATA_ENTRY_MODE_SETTING, 0x03);  // Ram data entry mode -> X and Y increase

	write_reg_data(g, WRITE_LUT_REG, LUTDefault_full, sizeof(LUTDefault_full)/sizeof(LUTDefault_full[0])); // Initialize the LUT full

	write_reg(g, DISPLAY_UPDATE_CTRL2, 0xC0);     // Power ON the display
	write_cmd(g, MASTER_ACTIVATION);
	write_reg(g, DEEP_SLEEP_MODE, 0x00);

	gU8 zeros[2] = { 0, 0 };
	write_reg(g, SET_RAM_X_CNT, 0x00);            // Set cursor at origin
	write_reg_data(g, SET_RAM_Y_CNT, zeros, 2);

	gU8 dataX[2] = { 0, (GDISP_SCREEN_WIDTH-1)/8 };
	gU8 dataY[4] = { 0, 0, (GDISP_SCREEN_HEIGHT-1)%256, (GDISP_SCREEN_HEIGHT-1)/256 };
	write_reg_data(g, SET_RAM_X_ADR, dataX, 2);   // Set viewport for the whole screen
	write_reg_data(g, SET_RAM_Y_ADR, dataY, 4);

	release_bus(g);

	gfxSleepMilliseconds(1500); // Wait for the display to initialize

	/* Finish board initialization. */
	post_init_board(g);

	/* Initialise the GDISP structure */
	g->g.Width = GDISP_SCREEN_WIDTH;
	g->g.Height = GDISP_SCREEN_HEIGHT;
	g->g.Orientation = gOrientation0;
	g->g.Powermode = gPowerOn;
	return gTrue;
}

#if 0			// Not needed yet
	static void set_cursor(GDisplay *g) {
		gU8 dataY[2];
		
		dataY[0] = g->p.y % 256;  // Y-data is send in two bytes
		dataY[1] = g->p.y / 256;
		
		switch(g->g.Orientation) {
		default:
		case gOrientation0:
		case gOrientation180:
			write_reg(g, SET_RAM_X_CNT, g->p.x / WS29EPD_PPB);
			write_reg_data(g, SET_RAM_Y_CNT, dataY, 2);
			break;

		case gOrientation90:
		case gOrientation270:
			write_reg(g, SET_RAM_Y_CNT, g->p.x / WS29EPD_PPB);
			write_reg_data(g, SET_RAM_X_CNT, dataY, 2);
			break;
		}
	}

	static void set_viewport(GDisplay *g) {
		gU8 dataX[2];
		gU8 dataY[4];
		
		// Fill up the X and Y position buffers.
		dataX[0] = g->p.x / WS29EPD_PPB;
		dataX[1] = (g->p.x + g->p.cx - 1) / WS29EPD_PPB;

		dataY[0] = g->p.y % 256; // Y-data is 9-bits so send in two bytes
		dataY[1] = g->p.y / 256;
		dataY[2] = (g->p.y + g->p.cy - 1) % 256;
		dataY[3] = (g->p.y + g->p.cy - 1) / 256;

		switch(g->g.Orientation) {
		default:
		case gOrientation0:
		case gOrientation180:
			write_reg_data(g, SET_RAM_X_ADR, dataX, 2);
			write_reg_data(g, SET_RAM_Y_ADR, dataY, 4);
			break;
		case gOrientation90:
		case gOrientation270:
			write_reg_data(g, SET_RAM_X_ADR, dataY, 4);
			write_reg_data(g, SET_RAM_Y_ADR, dataX, 2);
			break;
		}
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
	/* There is only black and no black (white). */
	if (gdispColor2Native(g->p.color) != Black) // Indexing in the array is done as described in the init routine
		((gU8 *)g->priv)[(GDISP_SCREEN_HEIGHT*(x/WS29EPD_PPB)) + y] |= (1 << (WS29EPD_PPB-1 - (x % WS29EPD_PPB)));
	else
		((gU8 *)g->priv)[(GDISP_SCREEN_HEIGHT*(x/WS29EPD_PPB)) + y] &= ~(1 << (WS29EPD_PPB-1 - (x % WS29EPD_PPB)));
}
#endif

#if GDISP_HARDWARE_FLUSH
LLDSPEC void gdisp_lld_flush(GDisplay *g) {
	acquire_bus(g);
	
	/* Start writing frame buffer to ram. */
	write_cmd(g, WRITE_RAM);
	
	for(int i=0; i<GDISP_SCREEN_HEIGHT; i++)
		for(int j=0; j<=((GDISP_SCREEN_WIDTH-1)/8); j++)
			write_data(g, ((gU8 *)g->priv)[(GDISP_SCREEN_HEIGHT*j) + i]);
		
	/* Update the screen. */
	write_reg(g, DISPLAY_UPDATE_CTRL2, 0xc7);  // Full update (partial hasn't been implemented yet)
	write_cmd(g, MASTER_ACTIVATION);
	write_cmd(g, NOP);
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
			case gPowerSleep:
			case gPowerDeepSleep:
				acquire_bus(g); // Put de display in deep sleep
				write_reg(g, DISPLAY_UPDATE_CTRL2, 0x03);
				write_reg(g, DEEP_SLEEP_MODE, 0x01);
				release_bus(g);
				break;
			case gPowerOn:
				acquire_bus(g); // Awake the display again
				write_reg(g, DISPLAY_UPDATE_CTRL2, 0xC0);
				write_reg(g, DEEP_SLEEP_MODE, 0x00);
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
			g->g.Height = GDISP_SCREEN_HEIGHT;
			g->g.Width = GDISP_SCREEN_WIDTH;
			break;
		case gOrientation90:
			g->g.Height = GDISP_SCREEN_WIDTH;
			g->g.Width = GDISP_SCREEN_HEIGHT;
			break;
		case gOrientation180:
			g->g.Height = GDISP_SCREEN_HEIGHT;
			g->g.Width = GDISP_SCREEN_WIDTH;
			break;
		case gOrientation270:
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

#endif	// GFX_USE_GDISP
