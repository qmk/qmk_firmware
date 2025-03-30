// Copyright 2021 Paul Cotter (@gr1mr3aver)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ST77XX command opcodes

// System function commands
#define ST77XX_CMD_NOP 0x00          // No operation
#define ST77XX_CMD_RESET 0x01        // Software reset
#define ST77XX_GET_ID_INFO 0x04      // Get ID information
#define ST77XX_GET_STATUS 0x09       // Get status
#define ST77XX_GET_PWR_MODE 0x0A     // Get power mode
#define ST77XX_GET_MADCTL 0x0B       // Get mem access ctl
#define ST77XX_GET_PIX_FMT 0x0C      // Get pixel format
#define ST77XX_GET_IMG_FMT 0x0D      // Get image format
#define ST77XX_GET_SIG_MODE 0x0E     // Get signal mode
#define ST77XX_CMD_SLEEP_ON 0x10     // Enter sleep mode
#define ST77XX_CMD_SLEEP_OFF 0x11    // Exist sleep mode
#define ST77XX_CMD_PARTIAL_ON 0x12   // Enter partial mode
#define ST77XX_CMD_NORMAL_ON 0x13    // Exit partial mode
#define ST77XX_CMD_INVERT_OFF 0x20   // Exit inverted mode
#define ST77XX_CMD_INVERT_ON 0x21    // Enter inverted mode
#define ST77XX_SET_GAMMA 0x26        // Set gamma params
#define ST77XX_CMD_DISPLAY_OFF 0x28  // Disable display
#define ST77XX_CMD_DISPLAY_ON 0x29   // Enable display
#define ST77XX_SET_COL_ADDR 0x2A     // Set column address
#define ST77XX_SET_ROW_ADDR 0x2B     // Set page (row) address
#define ST77XX_SET_MEM 0x2C          // Set memory
#define ST77XX_GET_MEM 0x2E          // Get memory
#define ST77XX_SET_PARTIAL_AREA 0x30 // Set partial area
#define ST77XX_CMD_TEARING_OFF 0x34  // Tearing line disabled
#define ST77XX_CMD_TEARING_ON 0x35   // Tearing line enabled
#define ST77XX_SET_MADCTL 0x36       // Set mem access ctl
#define ST77XX_CMD_IDLE_OFF 0x38     // Exit idle mode
#define ST77XX_CMD_IDLE_ON 0x39      // Enter idle mode
#define ST77XX_SET_PIX_FMT 0x3A      // Set pixel format
#define ST77XX_GET_ID1 0xDA          // Get ID1
#define ST77XX_GET_ID2 0xDB          // Get ID2
#define ST77XX_GET_ID3 0xDC          // Get ID3

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MADCTL Flags
#define ST77XX_MADCTL_MY 0b10000000
#define ST77XX_MADCTL_MX 0b01000000
#define ST77XX_MADCTL_MV 0b00100000
#define ST77XX_MADCTL_ML 0b00010000
#define ST77XX_MADCTL_RGB 0b00000000
#define ST77XX_MADCTL_BGR 0b00001000
#define ST77XX_MADCTL_MH 0b00000100
