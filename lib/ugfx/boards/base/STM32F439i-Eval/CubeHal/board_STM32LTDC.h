/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

// Avoid naming collisions with CubeHAL
#if GFX_COMPAT_V2 && GFX_COMPAT_OLDCOLORS
	#undef Red
	#undef Green
	#undef Blue
#endif

// Include CubeHAL
#include "stm32f4xx_hal.h"
#include "stm324x9i_eval_sdram.h"

#define ALLOW_2ND_LAYER		GFXON

// Panel parameters
// This panel is a AMPIRE640480 panel.

static const ltdcConfig driverCfg = {
	640, 480,								// Width, Height (pixels)
	30, 3,									// Horizontal, Vertical sync (pixels)
	114, 32,								// Horizontal, Vertical back porch (pixels)
	16, 10,									// Horizontal, Vertical front porch (pixels)
	0,										// Sync flags
	0x000000,								// Clear color (RGB888)

	{										// Background layer config
		(LLDCOLOR_TYPE *)SDRAM_DEVICE_ADDR, // Frame buffer address
		640, 480,							// Width, Height (pixels)
		640 * LTDC_PIXELBYTES,				// Line pitch (bytes)
		LTDC_PIXELFORMAT,					// Pixel format
		0, 0,								// Start pixel position (x, y)
		640, 480,							// Size of virtual layer (cx, cy)
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
		(LLDCOLOR_TYPE *)(SDRAM_DEVICE_ADDR+(640 * 480 * LTDC_PIXELBYTES)), // Frame buffer address
		640, 480,							// Width, Height (pixels)
		640 * LTDC_PIXELBYTES,				// Line pitch (bytes)
		LTDC_PIXELFORMAT,					// Pixel format
		0, 0,								// Start pixel position (x, y)
		640, 480,							// Size of virtual layer (cx, cy)
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

// LCD Clock values
#define LCD_PLLSAIN_VALUE			192					// 151
#define LCD_PLLSAIR_VALUE			2					// 3
#define LCD_PLLSAIDIVR_VALUE		RCC_PLLSAIDIVR_4	// RCC_PLLSAIDIVR_2

static void configureLcdClock(void)
{
	#if 1
		RCC_PeriphCLKInitTypeDef	periph_clk_init_struct;

		periph_clk_init_struct.PLLSAI.PLLSAIN = LCD_PLLSAIN_VALUE;
		periph_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
		periph_clk_init_struct.PLLSAI.PLLSAIR = LCD_PLLSAIR_VALUE;
		periph_clk_init_struct.PLLSAIDivR = LCD_PLLSAIDIVR_VALUE;
		HAL_RCCEx_PeriphCLKConfig(&periph_clk_init_struct);
	#else
		#define LCD_PLLSAIQ_VALUE                 7

		/* PLLSAI activation.*/
		RCC->PLLSAICFGR = (LCD_PLLSAIN_VALUE << 6) | (LCD_PLLSAIR_VALUE << 28) | (LCD_PLLSAIQ_VALUE << 24);
		RCC->DCKCFGR = (RCC->DCKCFGR & ~RCC_DCKCFGR_PLLSAIDIVR) | LCD_PLLSAIDIVR_VALUE;
		RCC->CR |= RCC_CR_PLLSAION;
		while(!(RCC->CR & RCC_CR_PLLSAIRDY));			// wait for PLLSAI to lock
	#endif
}

static void configureLcdPins(void)
{
	GPIO_InitTypeDef			GPIO_Init_Structure;

	// Enable peripheral clocks
	__GPIOI_CLK_ENABLE();
	__GPIOJ_CLK_ENABLE();
	__GPIOK_CLK_ENABLE();

	/*** LTDC Pins configuration ***/
	// GPIOI
	GPIO_Init_Structure.Pin       = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
	GPIO_Init_Structure.Pull      = GPIO_NOPULL;
	GPIO_Init_Structure.Speed     = GPIO_SPEED_FAST;
	GPIO_Init_Structure.Alternate = GPIO_AF14_LTDC;
	HAL_GPIO_Init(GPIOI, &GPIO_Init_Structure);

	// GPIOJ
	GPIO_Init_Structure.Pin       = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | \
	                                GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | \
	                                GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | \
	                                GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
	GPIO_Init_Structure.Pull      = GPIO_NOPULL;
	GPIO_Init_Structure.Speed     = GPIO_SPEED_FAST;
	GPIO_Init_Structure.Alternate = GPIO_AF14_LTDC;
	HAL_GPIO_Init(GPIOJ, &GPIO_Init_Structure);

	// GPIOK configuration
	GPIO_Init_Structure.Pin       = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | \
	                                GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
	GPIO_Init_Structure.Pull      = GPIO_NOPULL;
	GPIO_Init_Structure.Speed     = GPIO_SPEED_FAST;
	GPIO_Init_Structure.Alternate = GPIO_AF14_LTDC;
	HAL_GPIO_Init(GPIOK, &GPIO_Init_Structure);
}

static GFXINLINE void init_board(GDisplay* g)
{
	(void) g;

	// Set LCD pixel clock rate
	configureLcdClock();

	// Set pin directions
	configureLcdPins();

	// Initialise the SDRAM
	BSP_SDRAM_Init();
}

static GFXINLINE void post_init_board(GDisplay* g)
{
	(void) g;
}

static GFXINLINE void set_backlight(GDisplay* g, gU8 percent)
{
	(void) g;
	(void) percent;
}

#endif /* _GDISP_LLD_BOARD_H */
