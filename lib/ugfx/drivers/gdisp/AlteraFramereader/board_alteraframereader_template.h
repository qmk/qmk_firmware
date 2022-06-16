/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#define SCREEN_WIDTH            800
#define SCREEN_HEIGHT           480
#define FRAMEREADER_BASE        ALT_VIP_VFR_0_BASE

#if GDISP_NEED_CONTROL
	static void board_backlight(GDisplay* g, gU8 percent)
	{
		(void)g;
		(void)percent;
	}

	static void board_contrast(GDisplay* g, gU8 percent)
	{
		(void)g;
		(void)percent;
	}

	static void board_power(GDisplay* g, gPowermode pwr)
	{
		(void)g;
		(void)pwr;
	}
#endif
