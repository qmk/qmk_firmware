/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GINPUT_LLD_MOUSE_BOARD_H
#define _GINPUT_LLD_MOUSE_BOARD_H

#include "ft6x06.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

// Resolution and Accuracy Settings
#define GMOUSE_FT6x06_PEN_CALIBRATE_ERROR			40
#define GMOUSE_FT6x06_PEN_CLICK_ERROR				16
#define GMOUSE_FT6x06_PEN_MOVE_ERROR				14
#define GMOUSE_FT6x06_FINGER_CALIBRATE_ERROR		50
#define GMOUSE_FT6x06_FINGER_CLICK_ERROR			28
#define GMOUSE_FT6x06_FINGER_MOVE_ERROR				24

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_FT6x06_BOARD_DATA_SIZE				0

/* The FT6x06 I2C slave address */
#define FT6x06_SLAVE_ADDR 0x54

I2C_HandleTypeDef i2cHandle;
/* Maximum speed (400kHz) */
#define CLOCKSPEED 400000;

static gBool init_board(GMouse* m, unsigned instance) {
	(void)m;
	(void)instance;

	GPIO_InitTypeDef gpioInit;
	/* I2C1_SCL PB8 */
	__HAL_RCC_GPIOB_CLK_ENABLE();					// Enable GPIOB clock
	gpioInit.Pin = GPIO_PIN_8;
	gpioInit.Mode = GPIO_MODE_AF_OD;				// I2C -> Open-drain
	gpioInit.Pull = GPIO_NOPULL;					// Open-drain -> no pull
	gpioInit.Speed = GPIO_SPEED_FREQ_HIGH;			// High speed
	gpioInit.Alternate = GPIO_AF4_I2C1;			    // Alternate function 4
	HAL_GPIO_Init(GPIOB, &gpioInit);

	/* I2C1_SDA PB9 */
	gpioInit.Pin = GPIO_PIN_9;
	HAL_GPIO_Init(GPIOB, &gpioInit);

	/* LCD_INT PJ5 */
	__HAL_RCC_GPIOJ_CLK_ENABLE();
	gpioInit.Pin = GPIO_PIN_5;
	gpioInit.Mode = GPIO_MODE_INPUT;				// Input mode
	gpioInit.Pull = GPIO_PULLUP;					// Pull-up
	HAL_GPIO_Init(GPIOJ, &gpioInit);

    /* I2C1 intialization */
    i2cHandle.Instance             = I2C1;
    i2cHandle.Init.ClockSpeed      = CLOCKSPEED;
    i2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE_2;           // Normal duty cycle
    i2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;   // No dual adressing needed
    i2cHandle.Init.OwnAddress1     = 0x00;
    i2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    i2cHandle.Init.OwnAddress2     = 0x00;
    i2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;   // All not needed so disabled
    i2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    __HAL_RCC_I2C1_CLK_ENABLE();

	if(HAL_I2C_Init(&i2cHandle) == HAL_OK)
		return gTrue;

	return gFalse;
}

static GFXINLINE void aquire_bus(GMouse* m) {
    (void)m;
}

static GFXINLINE void release_bus(GMouse* m) {
    (void)m;
}

static void write_reg(GMouse* m, gU8 reg, gU8 val) {
    (void)m;

    HAL_I2C_Mem_Write(&i2cHandle, FT6x06_SLAVE_ADDR, (gU16)reg, I2C_MEMADD_SIZE_8BIT, &val, 1, 1000);
}

static gU8 read_byte(GMouse* m, gU8 reg) {
    (void)m;
    gU8 result;

    HAL_I2C_Mem_Read(&i2cHandle, FT6x06_SLAVE_ADDR, (gU16)reg, I2C_MEMADD_SIZE_8BIT, &result, 1, 1000);

    return result;
}

static gU16 read_word(GMouse* m, gU8 reg) {
	(void)m;
	gU8 result[2];

    HAL_I2C_Mem_Read(&i2cHandle, FT6x06_SLAVE_ADDR, (gU16)reg, I2C_MEMADD_SIZE_8BIT, result, 2, 1000);

	return (result[0]<<8 | result[1]);

}

#endif /* _GINPUT_LLD_MOUSE_BOARD_H */
