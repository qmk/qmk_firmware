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

#define GC9A01_PIXEL_FORMAT_12_BPP_MCUIF 0x03 // 12 bits/pixel MCU interface format
#define GC9A01_PIXEL_FORMAT_16_BPP_MCUIF 0x05 // 16 bits/pixel MCU interface format
#define GC9A01_PIXEL_FORMAT_18_BPP_MCUIF 0x06 // 18 bits/pixel MCU interface format
#define GC9A01_PIXEL_FORMAT_16_BPP_RGBIF 0x05 // 16 bits/pixel MCU interface format
#define GC9A01_PIXEL_FORMAT_18_BPP_RGBIF 0x06 // 18 bits/pixel MCU interface format

#define GC9A01_SOURCE_OUTPUT_SCAN_DIRECTION_S1_TO_S360 0b00000000
#define GC9A01_SOURCE_OUTPUT_SCAN_DIRECTION_S360_TO_S1 0b00100000
#define GC9A01_GATE_OUTPUT_SCAN_DIRECTION_G1_TO_G32 0b00000000
#define GC9A01_GATE_OUTPUT_SCAN_DIRECTION_G32_TO_G1 0b01000000
#define GC9A01_SCAN_MODE_INTER 0x10

#define GC9A01_LCD_DRIVE_LINE_16 0x01
#define GC9A01_LCD_DRIVE_LINE_24 0x02
#define GC9A01_LCD_DRIVE_LINE_32 0x03
#define GC9A01_LCD_DRIVE_LINE_40 0x04
#define GC9A01_LCD_DRIVE_LINE_48 0x05
#define GC9A01_LCD_DRIVE_LINE_56 0x06
#define GC9A01_LCD_DRIVE_LINE_64 0x07
#define GC9A01_LCD_DRIVE_LINE_72 0x08
#define GC9A01_LCD_DRIVE_LINE_80 0x09
#define GC9A01_LCD_DRIVE_LINE_88 0x0A
#define GC9A01_LCD_DRIVE_LINE_96 0x0B
#define GC9A01_LCD_DRIVE_LINE_104 0x0C
#define GC9A01_LCD_DRIVE_LINE_112 0x0D
#define GC9A01_LCD_DRIVE_LINE_120 0x0E
#define GC9A01_LCD_DRIVE_LINE_128 0x0F
#define GC9A01_LCD_DRIVE_LINE_136 0x10
#define GC9A01_LCD_DRIVE_LINE_144 0x11
#define GC9A01_LCD_DRIVE_LINE_152 0x12
#define GC9A01_LCD_DRIVE_LINE_160 0x13
#define GC9A01_LCD_DRIVE_LINE_168 0x14
#define GC9A01_LCD_DRIVE_LINE_176 0x15
#define GC9A01_LCD_DRIVE_LINE_184 0x16
#define GC9A01_LCD_DRIVE_LINE_192 0x17
#define GC9A01_LCD_DRIVE_LINE_200 0x18
#define GC9A01_LCD_DRIVE_LINE_208 0x19
#define GC9A01_LCD_DRIVE_LINE_216 0x1A
#define GC9A01_LCD_DRIVE_LINE_224 0x1B
#define GC9A01_LCD_DRIVE_LINE_232 0x1C
#define GC9A01_LCD_DRIVE_LINE_240 0x1D




