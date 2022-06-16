/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

/* Avoid naming collisions with CubeHAL. */
#if GFX_COMPAT_V2 && GFX_COMPAT_OLDCOLORS
	#undef Red
	#undef Green
	#undef Blue
#endif

/* HAL drivers needed for configuration. */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_dsi.h"
/* sdram driver provided by ST. */
#include "stm32f469i_discovery_sdram.h"
/* OTM8009A driver provided by ST. */
#include "otm8009a.h"

/** Manually set the LTDC timing. */
#ifndef GFX_LTDC_TIMING_SET
  #define GFX_LTDC_TIMING_SET
#endif

/** Most boards will be revision A. */
#ifndef USE_STM32469I_DISCO_REVA
  #define USE_STM32469I_DISCO_REVA
#endif

/** @brief Panel parameters
 *
 * This panel is a KoD KM-040TMP-02-0621 DSI LCD Display.
 */

static const ltdcConfig driverCfg = {
	800, 480,								// Width, Height (pixels)
	1, 2,									  // Horizontal, Vertical sync (pixels)
	15, 34,									// Horizontal, Vertical back porch (pixels)
	16, 34,									// Horizontal, Vertical front porch (pixels)
	0,										  // Sync flags
	0x000000,								// Clear color (RGB888)

	{										                  // Background layer config
		(LLDCOLOR_TYPE *)SDRAM_DEVICE_ADDR, // Frame buffer address
		800, 480,							              // Width, Height (pixels)
		800 * LTDC_PIXELBYTES,				      // Line pitch (bytes)
		LTDC_PIXELFORMAT,					          // Pixel format
		0, 0,								                // Start pixel position (x, y)
		800, 480,							              // Size of virtual layer (cx, cy)
		LTDC_COLOR_FUCHSIA,					        // Default color (ARGB8888)
		0x980088,							              // Color key (RGB888)
		LTDC_BLEND_FIX1_FIX2,				        // Blending factors
		0,									                // Palette (RGB888, can be NULL)
		0,									                // Palette length
		0xFF,								                // Constant alpha factor
		LTDC_LEF_ENABLE						          // Layer configuration flags
	},

	LTDC_UNUSED_LAYER_CONFIG				      // Foreground layer config
};

/** Display timing setting */
#define KoD_FREQUENCY_DIVIDER 7

/** Global DSI handle to hold DSI parameters. */
DSI_HandleTypeDef dsiHandle;

static GFXINLINE void reset_lcd(GDisplay* g);

/**
 * @brief  Function to intialize the STM32F46i-DISCO board.
 *
 * @param  g: Structure holding display parameters.
 */
static GFXINLINE void init_board(GDisplay *g) {

  // As we are not using multiple displays we set g->board to NULL as we don't use it
  g->board = 0;

#ifdef GFX_LTDC_TIMING_SET
  // KoD LCD clock configuration
  // PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz
  // PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 384 Mhz
  // PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 384/7 = 54.857 Mhz
  // LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_2 = 54.857/2 = 27.429Mhz
  #define STM32_SAISRC_NOCLOCK    (0 << 23)   /**< No clock.                  */
  #define STM32_SAISRC_PLL        (1 << 23)   /**< SAI_CKIN is PLL.           */
  #define STM32_SAIR_DIV2         (0 << 16)   /**< R divided by 2.            */
  #define STM32_SAIR_DIV4         (1 << 16)   /**< R divided by 4.            */
  #define STM32_SAIR_DIV8         (2 << 16)   /**< R divided by 8.            */
  #define STM32_SAIR_DIV16        (3 << 16)   /**< R divided by 16.           */

  #define STM32_PLLSAIN_VALUE                 384
  #define STM32_PLLSAIQ_VALUE                 4
  #define STM32_PLLSAIR_VALUE                 KoD_FREQUENCY_DIVIDER
  #define STM32_PLLSAIR_POST                  STM32_SAIR_DIV2

  RCC->PLLSAICFGR = (STM32_PLLSAIN_VALUE << 6) | (STM32_PLLSAIR_VALUE << 28) | (STM32_PLLSAIQ_VALUE << 24);
  RCC->DCKCFGR = (RCC->DCKCFGR & ~RCC_DCKCFGR_PLLSAIDIVR) | STM32_PLLSAIR_POST;
  RCC->CR |= RCC_CR_PLLSAION;
  while(!(RCC->CR & RCC_CR_PLLSAIRDY));			// wait for PLLSAI to lock
#endif

  __HAL_RCC_DSI_CLK_ENABLE();

  DSI_PLLInitTypeDef  dsiPllInit;
  DSI_CmdCfgTypeDef   dsiCmdMode;
  DSI_LPCmdTypeDef    dsiAPBCmd;
  /* Filling the DSI intialization struct. */
  dsiHandle.Instance                       = DSI;                            // There is only one DSI interface
  dsiHandle.Init.AutomaticClockLaneControl = DSI_AUTO_CLK_LANE_CTRL_ENABLE;  // Automatic clock lane control: powers down the clock lane when not in use
  /* Highest speed = 500MHz. */
  gU16 laneByteClk_kHz = 62500; /* 500 MHz / 8 = 62.5 MHz = 62500 kHz */
  /* TXEscapeCkdiv = f(LaneByteClk)/15.62 = 4 -> 500MHz/4 = 25MHz datasheet says around 20MHz */
  dsiHandle.Init.TXEscapeCkdiv             = laneByteClk_kHz/15620;          // Low power clock relative to the laneByteClock
  dsiHandle.Init.NumberOfLanes             = DSI_TWO_DATA_LANES;             // Two data lines for the fastest transfer speed

  /* Fill in the command mode struct. */
  dsiCmdMode.VirtualChannelID              = 0;                              // The first virtual channel

  /* Select the appropriate color coding. */
#ifdef GDISP_PIXELFORMAT_RGB565
  dsiCmdMode.ColorCoding = DSI_RGB565;
#else
  dsiCmdMode.ColorCoding = DSI_RGB888;
#endif

  dsiCmdMode.CommandSize            = driverCfg.width;             // Amount of pixels sent at once -> one line at a time
  dsiCmdMode.TearingEffectSource    = DSI_TE_EXTERNAL;             // Use pin PJ2
  dsiCmdMode.TearingEffectPolarity  = DSI_TE_RISING_EDGE;
  dsiCmdMode.HSPolarity             = DSI_HSYNC_ACTIVE_HIGH;
  dsiCmdMode.VSPolarity             = DSI_VSYNC_ACTIVE_HIGH;
  dsiCmdMode.DEPolarity             = DSI_DATA_ENABLE_ACTIVE_HIGH;
  dsiCmdMode.VSyncPol               = DSI_VSYNC_FALLING;
  dsiCmdMode.AutomaticRefresh       = DSI_AR_ENABLE;               // Use the automatic refresh mode
  dsiCmdMode.TEAcknowledgeRequest   = DSI_TE_ACKNOWLEDGE_DISABLE;  // Not needed when using TE through GPIO

  /* GPIO configuration. */
  GPIO_InitTypeDef  gpioInit;
  /* PH7  LCD_RESET */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  gpioInit.Pin   = GPIO_PIN_7;
  gpioInit.Mode  = GPIO_MODE_OUTPUT_OD;
  gpioInit.Pull  = GPIO_NOPULL;
  gpioInit.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOH, &gpioInit);

  /* PJ2  DSIHOST_TE */
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  gpioInit.Pin        = GPIO_PIN_2;
  gpioInit.Mode       = GPIO_MODE_AF_PP;
  gpioInit.Alternate  = GPIO_AF13_DSI;
  HAL_GPIO_Init(GPIOJ, &gpioInit);

  /* PA3  LCD_BL_CTRL This pin is not physically connected. */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  gpioInit.Pin        = GPIO_PIN_3;
  gpioInit.Mode       = GPIO_MODE_OUTPUT_OD;
  HAL_GPIO_Init(GPIOA, &gpioInit);

  /* Fvco = f(CLKin/IDF) * 2 * NDIV;  fPHI = Fvco/(2*ODF) */
#if !defined(USE_STM32469I_DISCO_REVA)
  /* fPHI = CLKin*62.5;  Fvco = CLKin*125 */
  dsiPllInit.PLLNDIV  = 125;
  dsiPllInit.PLLIDF   = DSI_PLL_IN_DIV2;
#else
  /* fPHI = CLKin*20;   Fvco = CLKin*40 */
  dsiPllInit.PLLNDIV  = 100;
  dsiPllInit.PLLIDF   = DSI_PLL_IN_DIV5;
#endif
  dsiPllInit.PLLODF   = DSI_PLL_OUT_DIV1;

  /* Initialize the DSI peripheral. */
  HAL_DSI_Init(&dsiHandle, &dsiPllInit);

  DSI_PHY_TimerTypeDef  PhyTimings;
  /* Configure DSI PHY HS2LP and LP2HS timings. Datasheet says 95ns max */
  PhyTimings.ClockLaneHS2LPTime   = 35;
  PhyTimings.ClockLaneLP2HSTime   = 35;
  PhyTimings.DataLaneHS2LPTime    = 35;
  PhyTimings.DataLaneLP2HSTime    = 35;
  PhyTimings.DataLaneMaxReadTime  = 0;
  PhyTimings.StopWaitTime         = 10;
  HAL_DSI_ConfigPhyTimer(&dsiHandle, &PhyTimings);

  /* Configure adapted command mode. */
  HAL_DSI_ConfigAdaptedCommandMode(&dsiHandle, &dsiCmdMode);

  /* Hardware reset LCD */
  reset_lcd(g);

  /* Initialize the SDRAM */
  BSP_SDRAM_Init();
}

static GFXINLINE void set_backlight(GDisplay* g, gU8 percent)
{
	(void)g;
	(void)percent;
}

/**
 * @brief  Perform a hardware reset on the LCD.
 *
 * @param  g: Display parameter structure.
 */
static GFXINLINE void reset_lcd(GDisplay* g)
{
  (void)g;
  /* Hardware display reset. */
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_7, GPIO_PIN_RESET);
  gfxSleepMilliseconds(20);
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_7, GPIO_PIN_SET);
  gfxSleepMilliseconds(10);
  /* Turn on backlight. */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
}

/**
 * @brief  Extra initialization that is performed after the LTDC intialization.
 *
 * @param  g: Display paramter structure.
 */
static GFXINLINE void post_init_board(GDisplay* g)
{
  (void)g;
  DSI_LPCmdTypeDef dsiAPBCmd;

  /* Enable the DSI host and wrapper after the LTDC initialization
  To avoid any synchronization issue, the DSI shall be started after enabling the LTDC */
  HAL_DSI_Start(&dsiHandle);

  /* The configuration commands for the LCD have to be send through the dsiAPBCmd
  * interface as the adapted command mode only supports DCS, WMS and WMC commands. */
  dsiAPBCmd.LPGenShortWriteNoP    = DSI_LP_GSW0P_ENABLE;  // Put everything in low power mode
  dsiAPBCmd.LPGenShortWriteOneP   = DSI_LP_GSW1P_ENABLE;
  dsiAPBCmd.LPGenShortWriteTwoP   = DSI_LP_GSW2P_ENABLE;
  dsiAPBCmd.LPGenShortReadNoP     = DSI_LP_GSR0P_ENABLE;
  dsiAPBCmd.LPGenShortReadOneP    = DSI_LP_GSR1P_ENABLE;
  dsiAPBCmd.LPGenShortReadTwoP    = DSI_LP_GSR2P_ENABLE;
  dsiAPBCmd.LPGenLongWrite        = DSI_LP_GLW_ENABLE;
  dsiAPBCmd.LPDcsShortWriteNoP    = DSI_LP_DSW0P_ENABLE;
  dsiAPBCmd.LPDcsShortWriteOneP   = DSI_LP_DSW1P_ENABLE;
  dsiAPBCmd.LPDcsShortReadNoP     = DSI_LP_DSR0P_ENABLE;
  dsiAPBCmd.LPDcsLongWrite        = DSI_LP_DLW_ENABLE;
  HAL_DSI_ConfigCommand(&dsiHandle, &dsiAPBCmd);

  /* Configure the LCD. */
#ifdef GDISP_PIXELFORMAT_RGB565
  OTM8009A_Init(OTM8009A_FORMAT_RBG565, 1);
#else
  OTM8009A_Init(OTM8009A_FORMAT_RGB888, 1);
#endif

  /* Enable the tearing effect line. */
  HAL_DSI_ShortWrite(&dsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, DSI_SET_TEAR_ON, 0);  // Only V-Blanking info

  /* Disable the APB command mode again to go into adapted command mode. (going into high speed mode) */
  dsiAPBCmd.LPGenShortWriteNoP    = DSI_LP_GSW0P_DISABLE;
  dsiAPBCmd.LPGenShortWriteOneP   = DSI_LP_GSW1P_DISABLE;
  dsiAPBCmd.LPGenShortWriteTwoP   = DSI_LP_GSW2P_DISABLE;
  dsiAPBCmd.LPGenShortReadNoP     = DSI_LP_GSR0P_DISABLE;
  dsiAPBCmd.LPGenShortReadOneP    = DSI_LP_GSR1P_DISABLE;
  dsiAPBCmd.LPGenShortReadTwoP    = DSI_LP_GSR2P_DISABLE;
  dsiAPBCmd.LPGenLongWrite        = DSI_LP_GLW_DISABLE;
  dsiAPBCmd.LPDcsShortWriteNoP    = DSI_LP_DSW0P_DISABLE;
  dsiAPBCmd.LPDcsShortWriteOneP   = DSI_LP_DSW1P_DISABLE;
  dsiAPBCmd.LPDcsShortReadNoP     = DSI_LP_DSR0P_DISABLE;
  dsiAPBCmd.LPDcsLongWrite        = DSI_LP_DLW_DISABLE;
  HAL_DSI_ConfigCommand(&dsiHandle, &dsiAPBCmd);

  HAL_DSI_Refresh(&dsiHandle);
}

/**
  * @brief  DCS or Generic short/long write command
  * @param  NbrParams: Number of parameters. It indicates the write command mode:
  *                 If inferior to 2, a long write command is performed else short.
  * @param  pParams: Pointer to parameter values table.
  * @retval HAL status
  */
void DSI_IO_WriteCmd(gU32 NbrParams, gU8 *pParams)
{
  if(NbrParams <= 1)
  {
   HAL_DSI_ShortWrite(&dsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, pParams[0], pParams[1]);
  }
  else
  {
   HAL_DSI_LongWrite(&dsiHandle,  0, DSI_DCS_LONG_PKT_WRITE, NbrParams, pParams[NbrParams], pParams);
  }
}

/**
 * @brief  Delay function for the OTM8009A driver.
 *
 * @param  Delay: The requested delay in ms.
 */
void OTM8009A_IO_Delay(gU32 Delay)
{
  gfxSleepMilliseconds(Delay);
}

#endif /* _GDISP_LLD_BOARD_H */
