/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _WS29EPD_H_
#define _WS29EPD_H_

#include "gfx.h"

/* Register definitions. */
#define DRIVER_OUTPUT_CTRL          0x01
#define BOOSTER_SOFT_START_CTRL     0x0C
#define DEEP_SLEEP_MODE             0x10
#define DATA_ENTRY_MODE_SETTING     0x11

#define SWRESET                     0x12
#define TEMP_SENSOR_CTRL            0x1A
#define MASTER_ACTIVATION           0x20
#define DISPLAY_UPDATE_CTRL         0x21

#define DISPLAY_UPDATE_CTRL2        0x22
#define WRITE_RAM                   0x24
#define WRITE_VCOM_REG              0x2C
#define WRITE_LUT_REG               0x32

#define SET_DUMMY_LINE_PERIOD       0x3A
#define SET_GATE_LINE_WIDTH         0x3B
#define BORDER_WAVEFORM_CTRL        0x3C
#define SET_RAM_X_ADR               0x44

#define SET_RAM_Y_ADR               0x45
#define SET_RAM_X_CNT               0x4E
#define SET_RAM_Y_CNT               0x4F
#define NOP                         0xFF

#endif
