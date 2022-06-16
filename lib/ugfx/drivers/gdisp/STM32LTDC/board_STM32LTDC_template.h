/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#define ALLOW_2ND_LAYER		GFXON

static const ltdcConfig driverCfg = {
	480, 272,								// Width, Height (pixels)
	41, 10,									// Horizontal, Vertical sync (pixels)
	13, 2,									// Horizontal, Vertical back porch (pixels)
	32, 2,									// Horizontal, Vertical front porch (pixels)
	0,										// Sync flags
	0x000000,								// Clear color (RGB888)

	{										// Background layer config
		(LLDCOLOR_TYPE *)SDRAM_DEVICE_ADDR, // Frame buffer address
		480, 272,							// Width, Height (pixels)
		480 * LTDC_PIXELBYTES,				// Line pitch (bytes)
		LTDC_PIXELFORMAT,					// Pixel format
		0, 0,								// Start pixel position (x, y)
		480, 272,							// Size of virtual layer (cx, cy)
		0x00000000,							// Default color (ARGB8888)
		0x000000,							// Color key (RGB888)
		LTDC_BLEND_FIX1_FIX2,				// Blending factors
		0,									// Palette (RGB888, can be NULL)
		0,									// Palette length
		0xFF,								// Constant alpha factor
		LTDC_LEF_ENABLE						// Layer configuration flags
	},

#if ALLOW_2ND_LAYER
	{										// Foreground layer config (if turned on)
		(LLDCOLOR_TYPE *)(SDRAM_DEVICE_ADDR+(480 * 272 * LTDC_PIXELBYTES)), // Frame buffer address
		480, 272,							// Width, Height (pixels)
		480 * LTDC_PIXELBYTES,				// Line pitch (bytes)
		LTDC_PIXELFORMAT,					// Pixel format
		0, 0,								// Start pixel position (x, y)
		480, 272,							// Size of virtual layer (cx, cy)
		0x00000000,							// Default color (ARGB8888)
		0x000000,							// Color key (RGB888)
		LTDC_BLEND_MOD1_MOD2,				// Blending factors
		0,									// Palette (RGB888, can be NULL)
		0,									// Palette length
		0xFF,								// Constant alpha factor
		LTDC_LEF_ENABLE						// Layer configuration flags
	}
#else
	LTDC_UNUSED_LAYER_CONFIG
#endif
};

static GFXINLINE void init_board(GDisplay* g) {
	// This is function only called once with the display for the background layer.
	(void)g;
}

static GFXINLINE void post_init_board(GDisplay* g)
{
	// This is function may be called twice - once for the background display and once
	// for the foreground display.
	// Note: It doesn't get called for the foreground display unless gfxconf.h has been
	//		setup for two displays on this controller.
	(void)g;
}

static GFXINLINE void set_backlight(GDisplay* g, gU8 percent)
{
	// This is function may be called with the display for either the foreground
	// or the background layer.
	// Note: It can't be called for the foreground display unless gfxconf.h has been
	//		setup for two displays on this controller.
	(void)g;
	(void)percent;
}

#endif /* _GDISP_LLD_BOARD_H */
