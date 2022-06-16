/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#include "stm32f746g_discovery_sdram.h"

#ifndef GFX_LTDC_USE_DIRECTIO
	#define GFX_LTDC_USE_DIRECTIO	GFXON
#endif
#ifndef GFX_LTDC_TIMING_SET
	/* Options are:
	 *	0 - don't initialise the display VCO and LTDC clocks - something else will do it
	 *	1 - uGFX preferred timings (default)
	 *	2 - Alternate timings	
	 */
	#define GFX_LTDC_TIMING_SET		1
#endif

#if GFX_USE_OS_CHIBIOS && !GFX_USE_DIRECTIO
	#include "hal.h"
	#include "ch.h"
#else
	#include "stm32f7xx_hal_rcc.h"
	#include "stm32f7xx_hal_gpio.h"
#endif
#include <string.h>

#if !GFX_USE_OS_CHIBIOS
	#define AFRL	AFR[0]
	#define AFRH	AFR[1]
#endif

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

static void configureLcdPins(void) {
	#if GFX_USE_OS_CHIBIOS && !GFX_LTDC_USE_DIRECTIO
		palSetPadMode(GPIOI, GPIOI_LCD_R0,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PI15: LCD_R0
		palSetPadMode(GPIOJ, GPIOJ_LCD_R1,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ0 : LCD_R1
		palSetPadMode(GPIOJ, GPIOJ_LCD_R2,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ1 : LCD_R2
		palSetPadMode(GPIOJ, GPIOJ_LCD_R3,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ2 : LCD_R3
		palSetPadMode(GPIOJ, GPIOJ_LCD_R4,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ3 : LCD_R4
		palSetPadMode(GPIOJ, GPIOJ_LCD_R5,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ4 : LCD_R5
		palSetPadMode(GPIOJ, GPIOJ_LCD_R6,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ5 : LCD_R6
		palSetPadMode(GPIOJ, GPIOJ_LCD_R7,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ6 : LCD_R7
		palSetPadMode(GPIOJ, GPIOJ_LCD_G0,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ7 : LCD_G0
		palSetPadMode(GPIOJ, GPIOJ_LCD_G1,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ8 : LCD_G1
		palSetPadMode(GPIOJ, GPIOJ_LCD_G2,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ9 : LCD_G2
		palSetPadMode(GPIOJ, GPIOJ_LCD_G3,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ10: LCD_G3
		palSetPadMode(GPIOJ, GPIOJ_LCD_G4,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ11: LCD_G4
		palSetPadMode(GPIOK, GPIOK_LCD_G5,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PK0 : LCD_G5
		palSetPadMode(GPIOK, GPIOK_LCD_G6,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PK1 : LCD_G6
		palSetPadMode(GPIOK, GPIOK_LCD_G7,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PK2 : LCD_G7
		palSetPadMode(GPIOE, GPIOE_LCD_B0,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PE4 : LCD_B0
		palSetPadMode(GPIOJ, GPIOJ_LCD_B1,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ13: LCD_B1
		palSetPadMode(GPIOJ, GPIOJ_LCD_B2,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ14: LCD_B2
		palSetPadMode(GPIOJ, GPIOJ_LCD_B3,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PJ15: LCD_B3
		palSetPadMode(GPIOG, GPIOG_LCD_B4,		PAL_MODE_ALTERNATE(9)  | PAL_STM32_OSPEED_HIGHEST);		// PG12: LCD_B4
		palSetPadMode(GPIOK, GPIOK_LCD_B5,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PK4 : LCD_B5
		palSetPadMode(GPIOK, GPIOK_LCD_B6,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PK5 : LCD_B6
		palSetPadMode(GPIOK, GPIOK_LCD_B7,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PK6 : LCD_B7
		palSetPadMode(GPIOK, GPIOK_LCD_DE,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PK7 : LCD_DE
		palSetPadMode(GPIOI, GPIOI_LCD_VSYNC,	PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PI9 : LCD_VSYNC
		palSetPadMode(GPIOI, GPIOI_LCD_HSYNC,	PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PI10: LCD_HSYNC
		palSetPadMode(GPIOI, GPIOI_LCD_INT,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PI13: LCD_INT
		palSetPadMode(GPIOI, GPIOI_LCD_CLK,		PAL_MODE_ALTERNATE(14) | PAL_STM32_OSPEED_HIGHEST);		// PI14: LCD_CLK
		palSetPadMode(GPIOI, GPIOI_LCD_DISP,	PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);	// PI12: LCD_DISP_PIN
		palSetPadMode(GPIOK, GPIOK_LCD_BL_CTRL,	PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);	// PK3 : LCD_BL_CTRL
	#else

		//-------------------------------------------
		// Initialise port PE

		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
		GPIOE->MODER |= (
						  GPIO_MODER_MODER4_1							// PE4:  LCD_B0 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						);
		GPIOE->MODER &=~ (
						  GPIO_MODER_MODER4_0
						);
		GPIOE->OTYPER &=~ (
						  GPIO_OTYPER_OT_4
						);
		GPIOE->OSPEEDR |= (
						  GPIO_OSPEEDER_OSPEEDR4_0 | GPIO_OSPEEDER_OSPEEDR4_1
						);
		GPIOE->PUPDR &=~ (
						  GPIO_PUPDR_PUPDR4_0  | GPIO_PUPDR_PUPDR4_1
						);
		GPIOE->AFRL |= (
						  (14U << 4*4)
						);

		//-------------------------------------------
		// Initialise port PG

		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
		GPIOG->MODER |= (
						  GPIO_MODER_MODER12_1							// PG12:  LCD_B4 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(9)
						);
		GPIOG->MODER &=~ (
						  GPIO_MODER_MODER12_0
						);
		GPIOG->OTYPER &=~ (
						  GPIO_OTYPER_OT_12
						);
		GPIOG->OSPEEDR |= (
						  GPIO_OSPEEDER_OSPEEDR12_0 | GPIO_OSPEEDER_OSPEEDR12_1
						);
		GPIOG->PUPDR &=~ (
						  GPIO_PUPDR_PUPDR12_0  | GPIO_PUPDR_PUPDR12_1
						);
		GPIOG->AFRH |= (
						  ( 9U << 4*(12-8))
						);

		//-------------------------------------------
		// Initialise port PI

		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
		GPIOI->MODER |= (
						  GPIO_MODER_MODER9_1							// PI9:  LCD_VSYNC    - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER10_1							// PI10: LCD_HSYNC    - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER12_0							// PI12: LCD_DISP_PIN - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_OUTPUT_PUSHPULL
						| GPIO_MODER_MODER13_1							// PI13: LCD_INT      - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER14_1							// PI14: LCD_CLK      - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER15_1							// PI15: LCD_R0       - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						);
		GPIOI->MODER &=~ (
						  GPIO_MODER_MODER9_0
						| GPIO_MODER_MODER10_0
						| GPIO_MODER_MODER12_1
						| GPIO_MODER_MODER13_0
						| GPIO_MODER_MODER14_0
						| GPIO_MODER_MODER15_0
						);
		GPIOI->OTYPER &=~ (
						  GPIO_OTYPER_OT_9
						| GPIO_OTYPER_OT_10
						| GPIO_OTYPER_OT_12
						| GPIO_OTYPER_OT_13
						| GPIO_OTYPER_OT_14
						| GPIO_OTYPER_OT_15
						);
		GPIOI->OSPEEDR |= (
						  GPIO_OSPEEDER_OSPEEDR9_0  | GPIO_OSPEEDER_OSPEEDR9_1
						| GPIO_OSPEEDER_OSPEEDR10_0 | GPIO_OSPEEDER_OSPEEDR10_1
						| GPIO_OSPEEDER_OSPEEDR12_0 | GPIO_OSPEEDER_OSPEEDR12_1
						| GPIO_OSPEEDER_OSPEEDR13_0 | GPIO_OSPEEDER_OSPEEDR13_1
						| GPIO_OSPEEDER_OSPEEDR14_0 | GPIO_OSPEEDER_OSPEEDR14_1
						| GPIO_OSPEEDER_OSPEEDR15_0 | GPIO_OSPEEDER_OSPEEDR15_1
						);
		GPIOI->PUPDR &=~ (
						  GPIO_PUPDR_PUPDR9_0  | GPIO_PUPDR_PUPDR9_1
						| GPIO_PUPDR_PUPDR10_0 | GPIO_PUPDR_PUPDR10_1
						| GPIO_PUPDR_PUPDR12_0 | GPIO_PUPDR_PUPDR12_1
						| GPIO_PUPDR_PUPDR13_0 | GPIO_PUPDR_PUPDR13_1
						| GPIO_PUPDR_PUPDR14_0 | GPIO_PUPDR_PUPDR14_1
						| GPIO_PUPDR_PUPDR15_0 | GPIO_PUPDR_PUPDR15_1
						);
		GPIOI->AFRH |= (
						  (14U << 4*(9-8))
						| (14U << 4*(10-8))
						| ( 0U << 4*(12-8))
						| (14U << 4*(13-8))
						| (14U << 4*(14-8))
						| (14U << 4*(15-8))
						);

		//-------------------------------------------
		// Initialise port PJ

		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;
		GPIOJ->MODER |= (
						  GPIO_MODER_MODER0_1							// PJ0:  LCD_R1 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER1_1							// PJ1:  LCD_R2 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER2_1							// PJ2:  LCD_R3 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER3_1							// PJ3:  LCD_R4 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER4_1							// PJ4:  LCD_R5 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER5_1							// PJ5:  LCD_R6 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER6_1							// PJ6:  LCD_R7 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER7_1							// PJ7:  LCD_G0 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER8_1							// PJ8:  LCD_G1 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER9_1							// PJ9:  LCD_G2 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER10_1							// PJ10: LCD_G3 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER11_1							// PJ11: LCD_G4 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER13_1							// PJ13: LCD_B1 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER14_1							// PJ14: LCD_B2 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER15_1							// PJ15: LCD_B3 - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						);
		GPIOJ->MODER &=~ (
						  GPIO_MODER_MODER0_0
						| GPIO_MODER_MODER1_0
						| GPIO_MODER_MODER2_0
						| GPIO_MODER_MODER3_0
						| GPIO_MODER_MODER4_0
						| GPIO_MODER_MODER5_0
						| GPIO_MODER_MODER6_0
						| GPIO_MODER_MODER7_0
						| GPIO_MODER_MODER8_0
						| GPIO_MODER_MODER9_0
						| GPIO_MODER_MODER10_0
						| GPIO_MODER_MODER11_0
						| GPIO_MODER_MODER13_0
						| GPIO_MODER_MODER14_0
						| GPIO_MODER_MODER15_0
						);
		GPIOJ->OTYPER &=~ (
						  GPIO_OTYPER_OT_0
						| GPIO_OTYPER_OT_1
						| GPIO_OTYPER_OT_2
						| GPIO_OTYPER_OT_3
						| GPIO_OTYPER_OT_4
						| GPIO_OTYPER_OT_5
						| GPIO_OTYPER_OT_6
						| GPIO_OTYPER_OT_7
						| GPIO_OTYPER_OT_8
						| GPIO_OTYPER_OT_9
						| GPIO_OTYPER_OT_10
						| GPIO_OTYPER_OT_11
						| GPIO_OTYPER_OT_13
						| GPIO_OTYPER_OT_14
						| GPIO_OTYPER_OT_15
						);
		GPIOJ->OSPEEDR |= (
						  GPIO_OSPEEDER_OSPEEDR0_0  | GPIO_OSPEEDER_OSPEEDR0_1
						| GPIO_OSPEEDER_OSPEEDR1_0  | GPIO_OSPEEDER_OSPEEDR1_1
						| GPIO_OSPEEDER_OSPEEDR2_0  | GPIO_OSPEEDER_OSPEEDR2_1
						| GPIO_OSPEEDER_OSPEEDR3_0  | GPIO_OSPEEDER_OSPEEDR3_1
						| GPIO_OSPEEDER_OSPEEDR4_0  | GPIO_OSPEEDER_OSPEEDR4_1
						| GPIO_OSPEEDER_OSPEEDR5_0  | GPIO_OSPEEDER_OSPEEDR5_1
						| GPIO_OSPEEDER_OSPEEDR6_0  | GPIO_OSPEEDER_OSPEEDR6_1
						| GPIO_OSPEEDER_OSPEEDR7_0  | GPIO_OSPEEDER_OSPEEDR7_1
						| GPIO_OSPEEDER_OSPEEDR8_0  | GPIO_OSPEEDER_OSPEEDR8_1
						| GPIO_OSPEEDER_OSPEEDR9_0  | GPIO_OSPEEDER_OSPEEDR9_1
						| GPIO_OSPEEDER_OSPEEDR10_0 | GPIO_OSPEEDER_OSPEEDR10_1
						| GPIO_OSPEEDER_OSPEEDR11_0 | GPIO_OSPEEDER_OSPEEDR11_1
						| GPIO_OSPEEDER_OSPEEDR13_0 | GPIO_OSPEEDER_OSPEEDR13_1
						| GPIO_OSPEEDER_OSPEEDR14_0 | GPIO_OSPEEDER_OSPEEDR14_1
						| GPIO_OSPEEDER_OSPEEDR15_0 | GPIO_OSPEEDER_OSPEEDR15_1
						);
		GPIOJ->PUPDR &=~ (
						  GPIO_PUPDR_PUPDR0_0  | GPIO_PUPDR_PUPDR0_1
						| GPIO_PUPDR_PUPDR1_0  | GPIO_PUPDR_PUPDR1_1
						| GPIO_PUPDR_PUPDR2_0  | GPIO_PUPDR_PUPDR2_1
						| GPIO_PUPDR_PUPDR3_0  | GPIO_PUPDR_PUPDR3_1
						| GPIO_PUPDR_PUPDR4_0  | GPIO_PUPDR_PUPDR4_1
						| GPIO_PUPDR_PUPDR5_0  | GPIO_PUPDR_PUPDR5_1
						| GPIO_PUPDR_PUPDR6_0  | GPIO_PUPDR_PUPDR6_1
						| GPIO_PUPDR_PUPDR7_0  | GPIO_PUPDR_PUPDR7_1
						| GPIO_PUPDR_PUPDR8_0  | GPIO_PUPDR_PUPDR8_1
						| GPIO_PUPDR_PUPDR9_0  | GPIO_PUPDR_PUPDR9_1
						| GPIO_PUPDR_PUPDR10_0 | GPIO_PUPDR_PUPDR10_1
						| GPIO_PUPDR_PUPDR11_0 | GPIO_PUPDR_PUPDR11_1
						| GPIO_PUPDR_PUPDR13_0 | GPIO_PUPDR_PUPDR13_1
						| GPIO_PUPDR_PUPDR14_0 | GPIO_PUPDR_PUPDR14_1
						| GPIO_PUPDR_PUPDR15_0 | GPIO_PUPDR_PUPDR15_1
						);
		GPIOJ->AFRL |= (
						  (14U << 4*0)
						| (14U << 4*1)
						| (14U << 4*2)
						| (14U << 4*3)
						| (14U << 4*4)
						| (14U << 4*5)
						| (14U << 4*6)
						| (14U << 4*7)
						);
		GPIOJ->AFRH |= (
						  (14U << 4*(8-8))
						| (14U << 4*(9-8))
						| (14U << 4*(10-8))
						| (14U << 4*(11-8))
						| (14U << 4*(13-8))
						| (14U << 4*(14-8))
						| (14U << 4*(15-8))
						);

		//-------------------------------------------
		// Initialise port PK

		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;
		GPIOK->MODER |= (
						  GPIO_MODER_MODER0_1							// PK0:  LCD_G5	     - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER1_1							// PK1:  LCD_G6      - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER2_1							// PK2:  LCD_G7      - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER3_0							// PK3:  LCD_BL_CTRL - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_OUTPUT_PUSHPULL
						| GPIO_MODER_MODER4_1							// PK4:  LCD_B5      - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER5_1							// PK5:  LCD_B6      - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER6_1							// PK6:  LCD_B7      - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						| GPIO_MODER_MODER7_1							// PK7:  LCD_DE      - PAL_STM32_OSPEED_HIGHEST, PAL_MODE_ALTERNATE(14)
						);
		GPIOK->MODER &=~ (
						  GPIO_MODER_MODER0_0
						| GPIO_MODER_MODER1_0
						| GPIO_MODER_MODER2_0
						| GPIO_MODER_MODER3_1
						| GPIO_MODER_MODER4_0
						| GPIO_MODER_MODER5_0
						| GPIO_MODER_MODER6_0
						| GPIO_MODER_MODER7_0
						);
		GPIOK->OTYPER &=~ (
						  GPIO_OTYPER_OT_0
						| GPIO_OTYPER_OT_1
						| GPIO_OTYPER_OT_2
						| GPIO_OTYPER_OT_3
						| GPIO_OTYPER_OT_4
						| GPIO_OTYPER_OT_5
						| GPIO_OTYPER_OT_6
						| GPIO_OTYPER_OT_7
						);
		GPIOK->OSPEEDR |= (
						  GPIO_OSPEEDER_OSPEEDR0_0  | GPIO_OSPEEDER_OSPEEDR0_1
						| GPIO_OSPEEDER_OSPEEDR1_0  | GPIO_OSPEEDER_OSPEEDR1_1
						| GPIO_OSPEEDER_OSPEEDR2_0  | GPIO_OSPEEDER_OSPEEDR2_1
						| GPIO_OSPEEDER_OSPEEDR3_0  | GPIO_OSPEEDER_OSPEEDR3_1
						| GPIO_OSPEEDER_OSPEEDR4_0  | GPIO_OSPEEDER_OSPEEDR4_1
						| GPIO_OSPEEDER_OSPEEDR5_0  | GPIO_OSPEEDER_OSPEEDR5_1
						| GPIO_OSPEEDER_OSPEEDR6_0  | GPIO_OSPEEDER_OSPEEDR6_1
						| GPIO_OSPEEDER_OSPEEDR7_0  | GPIO_OSPEEDER_OSPEEDR7_1
						);
		GPIOK->PUPDR &=~ (
						  GPIO_PUPDR_PUPDR0_0  | GPIO_PUPDR_PUPDR0_1
						| GPIO_PUPDR_PUPDR1_0  | GPIO_PUPDR_PUPDR1_1
						| GPIO_PUPDR_PUPDR2_0  | GPIO_PUPDR_PUPDR2_1
						| GPIO_PUPDR_PUPDR3_0  | GPIO_PUPDR_PUPDR3_1
						| GPIO_PUPDR_PUPDR4_0  | GPIO_PUPDR_PUPDR4_1
						| GPIO_PUPDR_PUPDR5_0  | GPIO_PUPDR_PUPDR5_1
						| GPIO_PUPDR_PUPDR6_0  | GPIO_PUPDR_PUPDR6_1
						| GPIO_PUPDR_PUPDR7_0  | GPIO_PUPDR_PUPDR7_1
						);
		GPIOK->AFRL |= (
						  (14U << 4*0)
						| (14U << 4*1)
						| (14U << 4*2)
						| ( 0U << 4*3)
						| (14U << 4*4)
						| (14U << 4*5)
						| (14U << 4*6)
						| (14U << 4*7)
						);
	#endif
}

static GFXINLINE void init_board(GDisplay *g) {
	(void) g;

	// Set pin directions
	configureLcdPins();

	// Enable the display and turn on the backlight
	#if GFX_USE_OS_CHIBIOS && !GFX_LTDC_USE_DIRECTIO
	    palSetPad(GPIOI, GPIOI_LCD_DISP);
	    palSetPad(GPIOK, GPIOK_LCD_BL_CTRL);
	#else
	    GPIOI->ODR |= (1 << 12);  // PowerOn
	    GPIOK->ODR |= (1 << 3);   // Backlight on
	#endif

	#if GFX_LTDC_TIMING_SET != 0
			#define STM32_SAISRC_NOCLOCK    (0 << 23)   /**< No clock.                  */
			#define STM32_SAISRC_PLL        (1 << 23)   /**< SAI_CKIN is PLL.           */
			#define STM32_SAIR_DIV2         (0 << 16)   /**< R divided by 2.            */
			#define STM32_SAIR_DIV4         (1 << 16)   /**< R divided by 4.            */
			#define STM32_SAIR_DIV8         (2 << 16)   /**< R divided by 8.            */
			#define STM32_SAIR_DIV16        (3 << 16)   /**< R divided by 16.           */

			// Some operating systems get these wrong eg ChibiOS - define our own values
			#undef STM32_PLLSAIN_VALUE
			#undef STM32_PLLSAIQ_VALUE
			#undef STM32_PLLSAIP_VALUE
			#undef STM32_PLLSAIR_VALUE

			/* Display timing */
			// RK043FN48H LCD clock configuration
			// PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz
			// PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 192 Mhz
			// PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 192/5 = 38.4 Mhz
			// LTDC clock frequency = PLLLCDCLK / STM32_PLLSAIR_POST = 38.4/4 = 9.6Mhz
			#if GFX_LTDC_TIMING_SET == 1
				#define RK043FN48H_FREQUENCY_DIVIDER		5
				#define STM32_PLLSAIN_VALUE                 192
				#define STM32_PLLSAIQ_VALUE                 4
				#define STM32_PLLSAIP_VALUE					4
				#define STM32_PLLSAIR_VALUE                 RK043FN48H_FREQUENCY_DIVIDER
				#define STM32_PLLSAIR_POST                  STM32_SAIR_DIV4
			#elif  GFX_LTDC_TIMING_SET == 2
				#define RK043FN48H_FREQUENCY_DIVIDER		4
				#define STM32_PLLSAIN_VALUE                 192
				#define STM32_PLLSAIQ_VALUE                 4
				#define STM32_PLLSAIP_VALUE					4
				#define STM32_PLLSAIR_VALUE                 RK043FN48H_FREQUENCY_DIVIDER
				#define STM32_PLLSAIR_POST                  STM32_SAIR_DIV4
			#else
				#error "LTDC: - Unknown timing set for the STM32F746-Discovery board"
			#endif

			RCC->CR &= ~RCC_CR_PLLSAION;
			RCC->PLLSAICFGR = ((STM32_PLLSAIP_VALUE/2-1)<<16) | (STM32_PLLSAIN_VALUE << 6) | (STM32_PLLSAIR_VALUE << 28) | (STM32_PLLSAIQ_VALUE << 24);
			RCC->DCKCFGR1 = (RCC->DCKCFGR1 & ~RCC_DCKCFGR1_PLLSAIDIVR) | STM32_PLLSAIR_POST;
			RCC->CR |= RCC_CR_PLLSAION;
			while(!(RCC->CR & RCC_CR_PLLSAIRDY));			// wait for PLLSAI to lock
	#endif

	// Initialise the SDRAM
	BSP_SDRAM_Init();
}

static GFXINLINE void post_init_board(GDisplay* g) {
	(void) g;
}

static GFXINLINE void set_backlight(GDisplay* g, gU8 percent) {
	(void) g;

	// ST was stupid enought not to hook this up to a pin that
	// is able to act as PWM output...
	#if GFX_USE_OS_CHIBIOS && !GFX_LTDC_USE_DIRECTIO
		if (percent <= 0) {
			palClearPad(GPIOK, GPIOK_LCD_BL_CTRL);  // Backlight off
		} else {
			palSetPad(GPIOK, GPIOK_LCD_BL_CTRL);    // Backlight on
		}
	#else
		if (percent <= 0) {
			GPIOK->ODR &=~ (1 << 3);	// Backlight off
		} else {
			GPIOK->ODR |= (1 << 3);		// Backlight on
		}
	#endif
}

#endif /* _GDISP_LLD_BOARD_H */
