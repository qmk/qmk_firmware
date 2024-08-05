// Copyright 2021 Paul Cotter (@gr1mr3aver)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter GC9A01 command opcodes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Level 1 command opcodes

#define GC9A01_GET_ID_INFO 0x04       // Get ID information
#define GC9A01_GET_STATUS 0x09        // Get status
#define GC9A01_CMD_SLEEP_ON 0x10      // Enter sleep mode
#define GC9A01_CMD_SLEEP_OFF 0x11     // Exit sleep mode
#define GC9A01_CMD_PARTIAL_ON 0x12    // Enter partial mode
#define GC9A01_CMD_PARTIAL_OFF 0x13   // Exit partial mode
#define GC9A01_CMD_INVERT_ON 0x20     // Enter inverted mode
#define GC9A01_CMD_INVERT_OFF 0x21    // Exit inverted mode
#define GC9A01_CMD_DISPLAY_OFF 0x28   // Disable display
#define GC9A01_CMD_DISPLAY_ON 0x29    // Enable display
#define GC9A01_SET_COL_ADDR 0x2A      // Set column address
#define GC9A01_SET_PAGE_ADDR 0x2B     // Set page address
#define GC9A01_SET_MEM 0x2C           // Set memory
#define GC9A01_SET_PARTIAL_AREA 0x30  // Set partial area
#define GC9A01_SET_VSCROLL 0x33       // Set vertical scroll def
#define GC9A01_CMD_TEARING_ON 0x34    // Tearing line enabled
#define GC9A01_CMD_TEARING_OFF 0x35   // Tearing line disabled
#define GC9A01_SET_MEM_ACS_CTL 0x36   // Set mem access ctl
#define GC9A01_SET_VSCROLL_ADDR 0x37  // Set vscroll start addr
#define GC9A01_CMD_IDLE_OFF 0x38      // Exit idle mode
#define GC9A01_CMD_IDLE_ON 0x39       // Enter idle mode
#define GC9A01_SET_PIX_FMT 0x3A       // Set pixel format
#define GC9A01_SET_MEM_CONT 0x3C      // Set memory continue
#define GC9A01_SET_TEAR_SCANLINE 0x44 // Set tearing scanline
#define GC9A01_GET_TEAR_SCANLINE 0x45 // Get tearing scanline
#define GC9A01_SET_BRIGHTNESS 0x51    // Set brightness
#define GC9A01_SET_DISPLAY_CTL 0x53   // Set display ctl
#define GC9A01_GET_ID1 0xDA           // Get ID1
#define GC9A01_GET_ID2 0xDB           // Get ID2
#define GC9A01_GET_ID3 0xDC           // Get ID3

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Level 2 command opcodes

#define GC9A01_SET_RGB_IF_SIG_CTL 0xB0     // RGB IF signal ctl
#define GC9A01_SET_BLANKING_PORCH_CTL 0xB5 // Set blanking porch ctl
#define GC9A01_SET_FUNCTION_CTL 0xB6       // Set function ctl
#define GC9A01_SET_TEARING_EFFECT 0xBA     // Set backlight ctl 3
#define GC9A01_SET_IF_CTL 0xF6             // Set interface control

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Level 3 command opcodes

#define GC9A01_SET_FRAME_RATE 0xE8        // Set frame rate
#define GC9A01_SET_SPI_2DATA 0xE9         // Set frame rate
#define GC9A01_SET_POWER_CTL_1 0xC1       // Set power ctl 1
#define GC9A01_SET_POWER_CTL_2 0xC3       // Set power ctl 2
#define GC9A01_SET_POWER_CTL_3 0xC4       // Set power ctl 3
#define GC9A01_SET_POWER_CTL_4 0xC9       // Set power ctl 4
#define GC9A01_SET_POWER_CTL_7 0xA7       // Set power ctl 7
#define GC9A01_SET_INTER_REG_ENABLE1 0xFE // Enable Inter Register 1
#define GC9A01_SET_INTER_REG_ENABLE2 0xEF // Enable Inter Register 2
#define GC9A01_SET_GAMMA1 0xF0            //
#define GC9A01_SET_GAMMA2 0xF1
#define GC9A01_SET_GAMMA3 0xF2
#define GC9A01_SET_GAMMA4 0xF3

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MADCTL Flags
#define GC9A01_MADCTL_MY 0b10000000
#define GC9A01_MADCTL_MX 0b01000000
#define GC9A01_MADCTL_MV 0b00100000
#define GC9A01_MADCTL_ML 0b00010000
#define GC9A01_MADCTL_RGB 0b00000000
#define GC9A01_MADCTL_BGR 0b00001000
#define GC9A01_MADCTL_MH 0b00000100
