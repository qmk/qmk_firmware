// Copyright 2022 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ST7735 additional command opcodes

// Panel Function Commands
#define ST7735_SET_FRAME_RATE_CTL_1 0xB1 // Set frame rate control 1
#define ST7735_SET_FRAME_RATE_CTL_2 0xB2 // Set frame rate control 2
#define ST7735_SET_FRAME_RATE_CTL_3 0xB3 // Set frame rate control 3
#define ST7735_SET_INVERSION_CTL 0xB4    // Set inversion mode control
#define ST7735_SET_DISPLAY_CTL 0xB6      // Set display control 5
#define ST7735_SET_POWER_CTL_1 0xC0      // Set GVDD
#define ST7735_SET_POWER_CTL_2 0xC1      // Set VGH and VGL
#define ST7735_SET_POWER_CTL_3 0xC2      // Set normal mode op amp current
#define ST7735_SET_POWER_CTL_4 0xC3      // Set idle mode op amp current
#define ST7735_SET_POWER_CTL_5 0xC4      // Set partial mode op amp current
#define ST7735_SET_VCOM_CTL 0xC5         // Set VCOM voltages
#define ST7735_SET_VCOM_OFFSET_CTL 0xC7  // Set VCOM offset ctl
#define ST7735_SET_LCD_ID 0xD1           // Set LCD module version
#define ST7735_SET_PROJECT_ID 0xD2       // Set product project ID
#define ST7735_SET_POWER_CTL_6 0xFC      // Set partial+idle op amp current
#define ST7735_SET_NVMEM_CTL_STATUS 0xD9 // EEPROM Control Status
#define ST7735_SET_NVMEM_READ_CMD 0xCC   // EEPROM Read Command
#define ST7735_SET_NVMEM_WRITE_CMD 0xDF  // EEPROM Write Command
#define ST7735_SET_PGAMMA 0xE0           // Set positive gamma
#define ST7735_SET_NGAMMA 0xE1           // Set negative gamma
#define ST7735_SET_EXTENSION_ENABLE 0xF0 // Enable extension command
#define ST7735_SET_VCOM_DELAY 0xFF       // Set VCOM delay time
