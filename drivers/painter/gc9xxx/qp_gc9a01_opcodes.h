// Copyright 2021 Paul Cotter (@gr1mr3aver)
// Copyright 2024 Fernando Birra
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter GC9A01 command opcodes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Level 1 command opcodes

#define GC9A01_SET_MEM_CONT 0x3C      // Set memory continue
#define GC9A01_SET_BRIGHTNESS 0x51    // Set brightness
#define GC9A01_SET_DISPLAY_CTL 0x53   // Set display ctl

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Level 2 command opcodes

#define GC9A01_SET_RGB_IF_SIG_CTL 0xB0     // RGB IF signal ctl
#define GC9A01_SET_BLANKING_PORCH_CTL 0xB5 // Set blanking porch ctl
#define GC9A01_SET_FUNCTION_CTL 0xB6       // Set function ctl
#define GC9A01_SET_TEARING_EFFECT 0xBA     // Set tering effect control
#define GC9A01_SET_IF_CTL 0xF6             // Set interface control

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Level 3 command opcodes

#define GC9A01_SET_POWER_CTL_7 0xA7       // Set power ctl 7

#define GC9A01_SET_POWER_CTL_1 0xC1       // Set power ctl 1
#define GC9A01_SET_POWER_CTL_2 0xC3       // Set power ctl 2
#define GC9A01_SET_POWER_CTL_3 0xC4       // Set power ctl 3
#define GC9A01_SET_POWER_CTL_4 0xC9       // Set power ctl 4

#define GC9A01_SET_FRAME_RATE 0xE8        // Set frame rate
#define GC9A01_SET_SPI_2DATA 0xE9         // Set frame rate

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
