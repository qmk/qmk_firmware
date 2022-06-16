/*
 * This board file is used for the following setup:
 * An ILI9488 display controller connected to an STM32F446VET micro controller through a 16-bit
 * parallel interface (Intel 8080 compatible). The FMC interface of the STM32 micro controller is used.
 * LCD_CS is hooked up to NE1 (first SRAM bank) and LCD_RS is hooked up to A16.
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#include "stm32f4xx_hal.h"

#define GDISP_REG              (*((volatile gU16 *) 0x60000000)) /* RS = 0 */
#define GDISP_RAM              (*((volatile gU16 *) 0x60020000)) /* RS = 1 */

static GFXINLINE void init_board(GDisplay *g)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  SRAM_HandleTypeDef hsram;
  FMC_NORSRAM_TimingTypeDef Timing;

  (void)g;

  // Peripheral clocks
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_FMC_CLK_ENABLE();

  // PC6 (backlight)
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  // PD3 (reset)
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  // FSMC
  {
    // Common GPIO configuration
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

    // GPIOD configuration
    GPIO_InitStruct.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7  | GPIO_PIN_8 |\
                                GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |  GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    // GPIOE configuration
    GPIO_InitStruct.Pin   = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |\
                                GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    // SRAM device configuration
    hsram.Instance = FMC_NORSRAM_DEVICE;
    hsram.Extended = FMC_NORSRAM_EXTENDED_DEVICE;

    // hsram.Init
    hsram.Init.NSBank = FMC_NORSRAM_BANK1;
    hsram.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
    hsram.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
    hsram.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
    hsram.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
    hsram.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
    hsram.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
    hsram.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
    hsram.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
    hsram.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
    hsram.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
    hsram.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
    hsram.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
    hsram.Init.WriteFifo = FMC_WRITE_FIFO_ENABLE;
    hsram.Init.PageSize = FMC_PAGE_SIZE_NONE;

    // Timings
    Timing.AddressSetupTime = 0;
    Timing.AddressHoldTime = 0;
    Timing.DataSetupTime = 150;
    Timing.BusTurnAroundDuration = 0;
    Timing.CLKDivision = 0;
    Timing.DataLatency = 0;
    Timing.AccessMode = FMC_ACCESS_MODE_A;

    HAL_SRAM_Init(&hsram, &Timing, NULL);
  }
}

static GFXINLINE void post_init_board(GDisplay* g)
{
	(void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, gBool state)
{
	(void) g;

  if (state) {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);
  }
}

static GFXINLINE void set_backlight(GDisplay* g, gU8 percent)
{
	(void) g;

	if (percent > 0) {
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	} else {
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	}
}

static GFXINLINE void acquire_bus(GDisplay* g)
{
	(void) g;
}

static GFXINLINE void release_bus(GDisplay* g)
{
	(void) g;
}

static GFXINLINE void write_index(GDisplay* g, gU16 index)
{
	(void) g;

  GDISP_REG = index;
}

static GFXINLINE void write_data(GDisplay* g, gU16 data)
{
	(void) g;

  GDISP_RAM = data;
}

static GFXINLINE void setreadmode(GDisplay* g)
{
	(void) g;
}

static GFXINLINE void setwritemode(GDisplay* g)
{
	(void) g;
}

static GFXINLINE gU16 read_data(GDisplay* g)
{
	(void) g;

	return (gU16)GDISP_RAM;
}

#endif /* _GDISP_LLD_BOARD_H */
