#include "stm32f4xx_hal.h"

#ifndef _GINPUT_LLD_MOUSE_BOARD_H
#define _GINPUT_LLD_MOUSE_BOARD_H

// Resolution and Accuracy Settings
#define GMOUSE_ADS7843_PEN_CALIBRATE_ERROR		8
#define GMOUSE_ADS7843_PEN_CLICK_ERROR			6
#define GMOUSE_ADS7843_PEN_MOVE_ERROR			4
#define GMOUSE_ADS7843_FINGER_CALIBRATE_ERROR	14
#define GMOUSE_ADS7843_FINGER_CLICK_ERROR		18
#define GMOUSE_ADS7843_FINGER_MOVE_ERROR		14

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_ADS7843_BOARD_DATA_SIZE			0

static SPI_HandleTypeDef _hspi;

static gBool init_board(GMouse* m, unsigned driverinstance)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  (void)m;
  (void)driverinstance;

  // Peripheral clocks
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_SPI1_CLK_ENABLE();

  // GPIO pins
  {
    // PA4 (chip select)
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = 0;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PA5 (SPI SCK)
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PA6 (SPI MISO)
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PA7 (SPI MOSI)
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PB1 (busy)
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = 0;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // PC4 (pen IRQ)
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  }

  // SPI
  _hspi.Instance = SPI1;
  _hspi.Init.Mode = SPI_MODE_MASTER;
  _hspi.Init.Direction = SPI_DIRECTION_2LINES;
  _hspi.Init.DataSize = SPI_DATASIZE_8BIT;
  _hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
  _hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
  _hspi.Init.NSS = SPI_NSS_SOFT;
  _hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  _hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
  _hspi.Init.TIMode = SPI_TIMODE_DISABLE;
  _hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  _hspi.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&_hspi) != HAL_OK) {
    return gFalse;
  }

  return gTrue;
}

static GFXINLINE gBool getpin_pressed(GMouse* m)
{
  (void)m;

  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4) == GPIO_PIN_RESET)
    return gTrue;

  return gFalse;
}

static GFXINLINE void aquire_bus(GMouse* m)
{
  (void)m;

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
}

static GFXINLINE void release_bus(GMouse* m)
{
  (void)m;

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

static GFXINLINE gU16 read_value(GMouse* m, gU16 reg)
{
  gU8 txbuf[3] = {0, 0, 0};
  gU8 rxbuf[3] = {0, 0, 0};
  gU16 ret;

  (void)m;

  txbuf[0] = reg;
  HAL_SPI_TransmitReceive(&_hspi, txbuf, rxbuf, 3, 1000);

  return (rxbuf[1] << 5) | (rxbuf[2] >> 3);
}

#endif /* _GINPUT_LLD_MOUSE_BOARD_H */
