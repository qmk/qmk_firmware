// Copyright 2021 Paul Cotter (@gr1mr3aver)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ST7789 additional command opcodes

// System function commands
#define ST7789_GET_SELF_DIAG 0x0F      // Get self-diagnostic result
#define ST7789_SET_VERT_SCRL 0x33      // Set vertical scroll definition
#define ST7789_SET_VERT_SCRL_ADDR 0x37 // SEt Vertical scroll start address
#define ST7789_SET_MEM_CONT 0x3C       // Memory Write continue
#define ST7789_GET_MEM_CONT 0x3E       // Memory Read continue
#define ST7789_SET_TEAR_LINE 0x44      // Set tear scanline
#define ST7789_GET_TEAR_LINE 0x45      // Get tear scanline
#define ST7789_SET_BRIGHTNESS 0x51     // Set display brightness
#define ST7789_GET_BRIGHTNESS 0x52     // Get display brightness
#define ST7789_SET_CTRL 0x53           // Set CTRL display
#define ST7789_GET_CTRL 0x54           // Get CTRL display value
#define ST7789_SET_CAB_COLOR 0x55      // Set content adaptive brightness control and color enhancement
#define ST7789_GET_CAB_COLOR 0x56      // Get content adaptive brightness control and color enhancement
#define ST7789_SET_CAB_BRIGHTNESS 0x5E // Set content adaptive minimum brightness
#define ST7789_GET_CAB_BRIGHTNESS 0x5F // Get content adaptive minimum brightness
#define ST7789_GET_ABC_SELF_DIAG 0x68  // Get Auto brightness control self diagnostics

// Panel Function Commands
#define ST7789_SET_RAM_CTL 0xB0            // Set RAM control
#define ST7789_SET_RGB_CTL 0xB1            // Set RGB control
#define ST7789_SET_PORCH_CTL 0xB2          // Set Porch control
#define ST7789_SET_FRAME_RATE_CTL_1 0xB3   // Set frame rate control 1
#define ST7789_SET_PARTIAL_CTL 0xB5        // Set Partial control
#define ST7789_SET_GATE_CTL 0xB7           // Set gate control
#define ST7789_SET_GATE_ON_TIMING 0xB8     // Set gate on timing adjustment
#define ST7789_SET_DIGITAL_GAMMA_ON 0xBA   // Enable digital gamma
#define ST7789_SET_VCOM 0xBB               // Set VCOM
#define ST7789_SET_POWER_SAVE 0xBC         // Set power saving mode
#define ST7789_SET_DISP_OFF_POWER 0xBD     // Set display off power saving
#define ST7789_SET_LCM_CTL 0xC0            // Set LCM control
#define ST7789_SET_IDS 0xC1                // Set IDs
#define ST7789_SET_VDV_VRH_ON 0xC2         // Set VDV and VRH command enable
#define ST7789_SET_VRH 0xC3                // Set VRH
#define ST7789_SET_VDV 0xC4                // Set VDV
#define ST7789_SET_VCOM_OFFSET 0xC5        // Set VCOM offset ctl
#define ST7789_SET_FRAME_RATE_CTL_2 0xC6   // Set frame rate control 2
#define ST7789_SET_CABC_CTL 0xC7           // Set CABC Control
#define ST7789_GET_REG_1 0xC8              // Get register value selection1
#define ST7789_GET_REG_2 0xCA              // Get register value selection2
#define ST7789_SET_PWM_FREQ 0xCC           // Set PWM frequency
#define ST7789_SET_POWER_CTL_1 0xD0        // Set power ctl 1
#define ST7789_SET_VAP_VAN_ON 0xD2         // Enable VAP/VAN signal output
#define ST7789_SET_CMD2_ENABLE 0xDF        // Enable command 2
#define ST7789_SET_PGAMMA 0xE0             // Set positive gamma
#define ST7789_SET_NGAMMA 0xE1             // Set negative gamma
#define ST7789_SET_DIGITAL_GAMMA_RED 0xE2  // Set digital gamma lookup table for red
#define ST7789_SET_DIGITAL_GAMMA_BLUE 0xE3 // Get digital gamma lookup table for blue
#define ST7789_SET_GATE_CTL_2 0xE4         // Set gate control 2
#define ST7789_SET_SPI2_ENABLE 0xE7        // Enable SPI2
#define ST7789_SET_POWER_CTL_2 0xE8        // Set power ctl 2
#define ST7789_SET_EQ_TIME_CTL 0xE9        // Set equalize time control
#define ST7789_SET_PROG_CTL 0xEC           // Set program control
#define ST7789_SET_PROG_MODE_ENABLE 0xFA   // Set program mode enable
#define ST7789_SET_NVMEM 0xFC              // Set NVMEM data
#define ST7789_SET_PROG_ACTION 0xFE        // Set program action
