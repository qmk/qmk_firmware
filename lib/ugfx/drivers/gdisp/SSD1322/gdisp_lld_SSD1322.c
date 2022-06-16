/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT			GDISPVMT_SSD1322
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"

#include "board_SSD1322.h"
#include <string.h>   // for memset

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT		64		// This controller should support  64
#endif
#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH		256
#endif
#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	100
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif
#ifndef SSD1322_USE_DMA
	#define SSD1322_USE_DMA			GFXOFF
#endif

#define SSD1322_ROW_WIDTH			(GDISP_SCREEN_WIDTH/2)

#define GDISP_FLG_NEEDFLUSH			(GDISP_FLG_DRIVER<<0)

#include "SSD1322.h"

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

// Some common routines and macros
#define RAM(g)							((gU8 *)g->priv)

// Some common routines and macros
#define xyaddr(x, y)		((x) + (y)*SSD1322_ROW_WIDTH)
#define xybits(x, y, c)		((c)<<(((x)&1)<<2))

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * As this controller can't update on a pixel boundary we need to maintain the
 * the entire display surface in memory so that we can do the necessary bit
 * operations. Fortunately it is a small display in 4 bit grayscale.
 * 64 * 128 / 2 = 4096 bytes.
 */

LLDSPEC gBool gdisp_lld_init(GDisplay *g) {
	// The private area is the display surface.
	g->priv = gfxAlloc(GDISP_SCREEN_HEIGHT * SSD1322_ROW_WIDTH);
	if (!g->priv)
		return gFalse;

	// Initialise the board interface
	init_board(g);
	post_init_board(g);

	// Hardware reset
	setpin_reset(g, gTrue);
	gfxSleepMilliseconds(20);
	setpin_reset(g, gFalse);
	gfxSleepMilliseconds(200);


	write_cmd(g,CMD_SET_COMMAND_LOCK);
	write_data(g,0x12); // Unlock OLED driver IC

	write_cmd(g,CMD_SET_DISPLAY_OFF);

	write_cmd(g,CMD_SET_CLOCK_DIVIDER);
	write_data(g,0x91);

    write_cmd(g,CMD_SET_MULTIPLEX_RATIO);
    write_data(g,0x3F); //duty = 1/64*,64 COMS are enabled

    write_cmd(g,CMD_SET_DISPLAY_OFFSET);
    write_data(g,0x00);

    write_cmd(g,CMD_SET_DISPLAY_START_LINE); //set start line position
    write_data(g,0x00);

    write_cmd(g,CMD_SET_REMAP);
    write_data(g,0x14);	//Horizontal address increment,Disable Column Address Re-map,Enable Nibble Re-map,Scan from COM[N-1] to COM0,Disable COM Split Odd Even
    write_data(g,0x11);	//Enable Dual COM mode

    write_cmd(g,0xB5); //GPIO
    write_data(g,0x00);
    //writeCommand(0x00);

    write_cmd(g,CMD_SET_FUNCTION_SELECTION);
    write_data(g,0x01);//  selection external VDD

    write_cmd(g,CMD_DISPLAY_ENHANCEMENT);
    write_data(g,0xA0);//	enables the external VSL
    write_data(g,0xb5);//	0xfd,Enhanced low GS display quality;default is 0xb5(normal),

    write_cmd(g,CMD_SET_CONTRAST_CURRENT);
    write_data(g,0x7f); // 0xff 	default is 0x7f

    write_cmd(g,CMD_MASTER_CURRENT_CONTROL);
    write_data(g,0x0f);	//default is 0x0f

    write_cmd(g,0xB9); //GRAY TABLE,linear Gray Scale

    write_cmd(g,CMD_SET_PHASE_LENGTH);
    write_data(g,0xE2);	// default is 0x74

    write_cmd(g,CMD_DISPLAY_ENHANCEMENT_B);
    write_data(g,0xA2);	// Reserved;default is 0xa2(normal)
    write_data(g,0x20);

    write_cmd(g,CMD_SET_PRECHARGE_VOLTAGE);
    write_data(g,0x1F);	// 0.6xVcc

    write_cmd(g,CMD_SET_SECOND_PRECHARGE_PERIOD);
    write_data(g,0x08);	// default

    write_cmd(g,CMD_SET_VCOMH_VOLTAGE	);
    write_data(g,0x07);	// 0.86xVcc;default is 0x04

    write_cmd(g,CMD_SET_DISPLAY_MODE_NORMAL);

    write_cmd(g,CMD_EXIT_PARTIAL_DISPLAY);

    write_cmd(g,CMD_SET_DISPLAY_ON);
    // Finish Init
    post_init_board(g);



	/* Initialise the GDISP structure */
	g->g.Width = GDISP_SCREEN_WIDTH;
	g->g.Height = GDISP_SCREEN_HEIGHT;
	g->g.Orientation = gOrientation180;
	g->g.Powermode = gPowerOn;
	g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
	g->g.Contrast = GDISP_INITIAL_CONTRAST;
	return gTrue;
}

#if GDISP_HARDWARE_FLUSH
	LLDSPEC void gdisp_lld_flush(GDisplay *g) {
		gU8 * ram;
		unsigned cols,rows;

		// Don't flush if we don't need it.
		if (!(g->flags & GDISP_FLG_NEEDFLUSH))
			return;

		acquire_bus(g);
		write_cmd(g, CMD_SET_COLUMN_ADDR);					// range 28 to 91  for 256 pixels to x
		write_data(g, 28);
		write_data(g, GDISP_SCREEN_WIDTH/4 + 28 - 1);
		write_cmd(g, CMD_SET_ROW_ADDR);						// range 0 to 63   for 64 pixels
		write_data(g, 0);
		write_data(g, GDISP_SCREEN_HEIGHT-1);
		write_cmd(g, CMD_WRITE_RAM);
		ram = RAM(g);
		#if SSD1322_USE_DMA
			write_data_DMA(g, ram);
		#else
			for(rows = 0; rows < GDISP_SCREEN_HEIGHT; rows ++) {
				for(cols = 0;cols < GDISP_SCREEN_WIDTH/2; cols ++) {
					write_data(g, *ram++);
				}
			}
		#endif
		release_bus(g);
		g->flags &= ~GDISP_FLG_NEEDFLUSH;
	}
#endif

#if GDISP_HARDWARE_DRAWPIXEL
	LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g) {
		gCoord		x, y;
		gU8		*ram;

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
		ram = RAM(g)+xyaddr(x,y);
		*ram &= ~xybits(x, y, LLDCOLOR_MASK());
		*ram |= xybits(x, y, gdispColor2Native(g->p.color));
		g->flags |= GDISP_FLG_NEEDFLUSH;
	}
#endif

#if GDISP_HARDWARE_PIXELREAD
	LLDSPEC gColor gdisp_lld_get_pixel_color(GDisplay *g) {
		gCoord			x, y;
		LLDCOLOR_TYPE	c;	

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
		c = (RAM(g)[xyaddr(x, y)]>>((x & 1)<<2)) & LLDCOLOR_MASK();
		return gdispNative2Color(c);
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
				write_cmd(g, CMD_SET_DISPLAY_MODE_OFF);
				release_bus(g);
				break;
			case gPowerOn:
				acquire_bus(g);
				write_cmd(g, CMD_SET_DISPLAY_MODE_ON);
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
			/* Rotation is handled by the drawing routines */
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
		}
	}
#endif // GDISP_NEED_CONTROL

#endif // GFX_USE_GDISP
