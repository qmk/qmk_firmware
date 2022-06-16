/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GINPUT_LLD_MOUSE_BOARD_H
#define _GINPUT_LLD_MOUSE_BOARD_H

#include <stdio.h>
#include <system.h>
#include "i2c_opencores.h"

#define FT5316_I2C_SLAVE_ADDRESS 0x38

// Resolution and Accuracy Settings
#define GMOUSE_FT5316_PEN_CALIBRATE_ERROR		8
#define GMOUSE_FT5316_PEN_CLICK_ERROR			6
#define GMOUSE_FT5316_PEN_MOVE_ERROR			4
#define GMOUSE_FT5316_FINGER_CALIBRATE_ERROR	14
#define GMOUSE_FT5316_FINGER_CLICK_ERROR		18
#define GMOUSE_FT5316_FINGER_MOVE_ERROR			14

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_FT5316_BOARD_DATA_SIZE			0

// Set this to GFXON if you want self-calibration.
//	NOTE:	This is not as accurate as real calibration.
//			It requires the orientation of the touch panel to match the display.
//			It requires the active area of the touch panel to exactly match the display size.
#define GMOUSE_FT5316_SELF_CALIBRATE			GFXON

static unsigned int device_write(unsigned char device_address, unsigned char sub_address, unsigned char wdata)
{
	I2C_start(I2C_OPENCORES_0_BASE, device_address, 0);			// Device address in write mode
	I2C_write(I2C_OPENCORES_0_BASE, sub_address, 0);			// Set sub address to read register
	I2C_write(I2C_OPENCORES_0_BASE, wdata, 1);					// Set write register

	return 1;
}

static unsigned int device_read(unsigned char device_address, unsigned char sub_address)
{
	unsigned int rdata;

	I2C_start(I2C_OPENCORES_0_BASE, device_address, 0);			// Device address in write mode
	rdata = I2C_write(I2C_OPENCORES_0_BASE, sub_address, 0);	// Set sub address to read register.
	I2C_start(I2C_OPENCORES_0_BASE, device_address, 1);			// Send start again but this time in read mode
	rdata = I2C_read(I2C_OPENCORES_0_BASE, 1);					// Read the register and send stop

	return rdata;
}

static unsigned int device_read_16(unsigned char device_address, unsigned char sub_address)
{
	unsigned int rdata_l;
	unsigned int rdata_h;

	I2C_start(I2C_OPENCORES_0_BASE, device_address, 0);			// Eccelerometer address in write mode
	rdata_l = I2C_write(I2C_OPENCORES_0_BASE, sub_address, 0);	// Set sub address to read register.
	I2C_start(I2C_OPENCORES_0_BASE, device_address, 1);			// Send start again but this time in read mode
	rdata_l = I2C_read(I2C_OPENCORES_0_BASE, 0);				// Read the register and MACK
	rdata_h = I2C_read(I2C_OPENCORES_0_BASE, 1);				// Read the next register and send stop

	return (0xFFFF & ((rdata_h << 8) | rdata_l));
}

static gBool init_board(GMouse* m, unsigned instance)
{
	(void)m;
	(void)instance;

	I2C_init(I2C_OPENCORES_0_BASE, 50000000, 400000);

	return gTrue;
}

static void write_reg(GMouse* m, gU8 reg, gU8 val)
{
	(void)m;

	device_write(FT5316_I2C_SLAVE_ADDRESS, reg, val);
}

static gU8 read_byte(GMouse* m, gU8 reg)
{
	(void)m;
	gU8 ret = 0;

	ret = (gU8)device_read(FT5316_I2C_SLAVE_ADDRESS, reg);

	return ret;
}

static gU16 read_word(GMouse* m, gU8 reg)
{
	(void)m;
	gU16 ret = 0;

	ret = (gU16)device_read(FT5316_I2C_SLAVE_ADDRESS, reg);

	return ret;
}

#endif /* _GINPUT_LLD_MOUSE_BOARD_H */
