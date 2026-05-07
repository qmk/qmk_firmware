// Copyright 2021 Paul Cotter (@gr1mr3aver)
// Copyright 2024 Fernando Birra
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter GC9xxx command opcodes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define GC9XXX_GET_ID_INFO 0x04 // Get ID information
#define GC9XXX_GET_STATUS 0x09  // Get status

#define GC9XXX_CMD_SLEEP_ON 0x10    // Enter sleep mode
#define GC9XXX_CMD_SLEEP_OFF 0x11   // Exit sleep mode
#define GC9XXX_CMD_PARTIAL_ON 0x12  // Enter partial mode
#define GC9XXX_CMD_PARTIAL_OFF 0x13 // Exit partial mode

#define GC9XXX_CMD_INVERT_OFF 0x20  // Exit inverted mode
#define GC9XXX_CMD_INVERT_ON 0x21   // Enter inverted mode
#define GC9XXX_CMD_DISPLAY_OFF 0x28 // Disable display
#define GC9XXX_CMD_DISPLAY_ON 0x29  // Enable display
#define GC9XXX_SET_COL_ADDR 0x2A    // Set column address (MSB(StartCol),LSB(StartCol),MSB(EndCol),LSB(EndCol)
#define GC9XXX_SET_ROW_ADDR 0x2B    // Set row address (MSB(StartRow),LSB(StartRow),MSB(EndRow),LSB(EndRow)
#define GC9XXX_SET_MEM 0x2C         // Set (write) memory

#define GC9XXX_SET_PARTIAL_AREA 0x30      // Set partial area (MSB(StartRow),LSB(StartRow),MSB(EndRow),LSB(EndRow)
#define GC9XXX_SET_VSCROLL 0x33           // Set vertical scroll MSB(TFA),LSB(TFA),MSB(VSA),LSB(VSA)+ GC9107 extra param: MSB(BFA),LSB(BFA)
#define GC9XXX_CMD_TEARING_OFF 0x34       // Tearing effect line OFF
#define GC9XXX_CMD_TEARING_ON 0x35        // Tearing effect line ON
#define GC9XXX_SET_MEM_ACS_CTL 0x36       // Set mem access ctl
#define GC9XXX_SET_VSCROLL_ADDR 0x37      // Set vscroll start addr
#define GC9XXX_CMD_IDLE_OFF 0x38          // Exit idle mode
#define GC9XXX_CMD_IDLE_ON 0x39           // Enter idle mode
#define GC9XXX_SET_PIXEL_FORMAT 0x3A      // Set pixel format
#define GC9XXX_SET_TEAR_SCANLINE 0x44     // Set tearing scanline (Scanline = LS bit of Param 1 (GC9A01) + Param 2(GC9XXX))
#define GC9XXX_GET_TEAR_SCANLINE 0x45     // Get tearing scanline (Scanline = LS bit of Param 1 (GC9A01) + Param 2(GC9XXX))
#define GC9XXX_GET_ID1 0xDA               // Get ID1
#define GC9XXX_GET_ID2 0xDB               // Get ID2
#define GC9XXX_GET_ID3 0xDC               // Get ID3
#define GC9XXX_SET_INTER_REG_ENABLE1 0xFE // Enable Inter Register 1
#define GC9XXX_SET_INTER_REG_ENABLE2 0xEF // Enable Inter Register 2
#define GC9XXX_SET_GAMMA1 0xF0            // Set gamma 1
#define GC9XXX_SET_GAMMA2 0xF1            // Set gamma 2

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MADCTL Flags
#define GC9XXX_MADCTL_MY 0b10000000 // Mirror Y (row address order)
#define GC9XXX_MADCTL_MX 0b01000000 // Mirror X (column address order)
#define GC9XXX_MADCTL_MV 0b00100000 // Vertical Refresh Order (bottom to top)
#define GC9XXX_MADCTL_ML 0b00010000
#define GC9XXX_MADCTL_BGR 0b00001000
#define GC9XXX_MADCTL_RGB 0b00000000

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GC9XXX Parameter constants
