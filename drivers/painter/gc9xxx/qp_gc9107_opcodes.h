// Copyright 2024 Fernando Birra
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter GC9107 command opcodes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define GC9107_GET_POWER_MODE 0x0A  // Get power mode
#define GC9107_GET_MADCTL 0x0B      // Get MADCTL
#define GC9107_GET_PIXEL_FMT 0x0C   // Get pixel format
#define GC9107_GET_IMAGE_FMT 0x0D   // Get image format
#define GC9107_GET_SIGNAL_MODE 0x0E // Get signal mode
#define GC9107_GET_DIAG_RESULT 0x0F // Get self-diagnostic results

#define GC9107_SET_FRAME_RATE 0xA8        // Set frame rate
#define GC9107_SET_COMPLEMENT_RGB 0xAC    // Set complement Principle RGB
#define GC9107_SET_BLANK_PORCH 0xAD       // Set blank porch control, 0;front_porch[6:0],0;back_porch[6:0]
#define GC9107_SET_FUNCTION_CTL1 0xB1     // Set access to AVDD_VCL_CLK and VGH_VGL_CLK commands
#define GC9107_SET_FUNCTION_CTL2 0xB2     // Set access to VGH, VGH control commands
#define GC9107_SET_FUNCTION_CTL3 0xB3     // Set access to Gamma control commands
#define GC9107_SET_DISPLAY_INVERSION 0xB4 // Set Display Inversion control
#define GC9107_SET_FUNCTION_CTL6 0xB6     // Set access to commands SET_FRAME_RATE, SET_COMPLEMENT_RGB and SET_BLANK_PORCH
#define GC9107_SET_CUSTOM_ID_INFO 0xD3    // Set customized display id information
#define GC9107_AVDD_VCL_CLK 0xE3          // AVDD_CLK
#define GC9107_SET_VGH 0xE8               // Set VGH
#define GC9107_SET_VGL 0xE9               // Set VGL
#define GC9107_SET_VGH_VGL_CLK 0xEA       // Set VGH and VGL clock divisors

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GC9107 Parameter constants

//      Parameter values for
//      GC9107_SET_PIXEL_FORMAT
#define GC9107_PIXEL_FORMAT_12_BPP_IFPF (0b001 << 0) // 12 bits per pixel
#define GC9107_PIXEL_FORMAT_16_BPP_IFPF (0b101 << 0) // 16 bits per pixel
#define GC9107_PIXEL_FORMAT_18_BPP_IFPB (0b110 << 0) // 18 bits per pixel

//      Parameter values for
//      GC9107_SET_COMPLEMENT_RGB
#define GC9107_COMPLEMENT_WITH_0 0x00   // R0 <- B0 <- 0, except if data is FFh
#define GC9107_COMPLEMENT_WITH_1 0x40   // R0 <- B0 <- 1, except if data is 00h
#define GC9107_COMPLEMENT_WITH_MSB 0x80 // R0 <- R5, B0 <- B5
#define GC9107_COMPLEMENT_WITH_LSB 0xC0 // R0 <- B0 <- G0
//      Parameter masks for
//      GC9107_SET_FUNCTION_CTL1
#define GC9107_ALLOW_AVDD_VCL_CLK 0b00001000 // Allow AVDD_VCL_CLK command
//      Parameter masks for
//      GC9107_SET_FUNCTION_CTL2
#define GC9107_ALLOW_SET_VGH 0b00000001         // Allow GC9107_SET_VGH
#define GC9107_ALLOW_SET_VGL 0b00000010         // Allow GC9107_SET_VGL
#define GC9107_ALLOW_SET_VGH_VGL_CLK 0b00000100 // Allow GC9107_SET_VGH_VGL_CLK
//      Parameter masks for
//      GC9107_SET_FUNCTION_CTL3
#define GC9107_ALLOW_SET_GAMMA1 0b00000001 // Allow GC9107_SET_GAMMA1
#define GC9107_ALLOW_SET_GAMMA2 0b00000010 // Allow GC9107_SET_GAMMA2
//      Parameter mask for
//      GC9107_SET_FUNCTION_CTL6
#define GC9107_ALLOW_SET_FRAMERATE 0b000000001      // Allow GC9107_SET_FRAME_RATE
#define GC9107_ALLOW_SET_COMPLEMENT_RGB 0b000010000 // Allow GC9107_SET_COMPLEMENT_RGB
#define GC9107_ALLOW_SET_BLANK_PORCH 0b000100000    // Allow GFC9107_SET_BLANK_PORCH
//      Parameter values for
//      AVDD_CLK_AD part (Most significant nibble)
#define GC9107_AVDD_CLK_AD_2T 0x00
#define GC9107_AVDD_CLK_AD_3T 0x10
#define GC9107_AVDD_CLK_AD_4T 0x20
#define GC9107_AVDD_CLK_AD_5T 0x30
#define GC9107_AVDD_CLK_AD_6T 0x40
#define GC9107_AVDD_CLK_AD_7T 0x50
#define GC9107_AVDD_CLK_AD_8T 0x60
#define GC9107_AVDD_CLK_AD_9T 0x70
//      Parameter values for
//      VCL_CLK_AD part (Least significant nibble)
#define GC9107_VCL_CLK_AD_2T 0x00
#define GC9107_VCL_CLK_AD_3T 0x01
#define GC9107_VCL_CLK_AD_4T 0x02
#define GC9107_VCL_CLK_AD_5T 0x03
#define GC9107_VCL_CLK_AD_6T 0x04
#define GC9107_VCL_CLK_AD_7T 0x05
#define GC9107_VCL_CLK_AD_8T 0x06
#define GC9107_VCL_CLK_AD_9T 0x07
//      Parameter values for
//      GC9107_SET_VGH
#define GC9107_VGH_P100 0x20 // +10 V
#define GC9107_VGH_P110 0x21 // +11 V
#define GC9107_VGH_P120 0x22 // +12 V
#define GC9107_VGH_P130 0x23 // +13 V
#define GC9107_VGH_P140 0x24 // +14 V
#define GC9107_VGH_P150 0x25 // +15 V
//      Parameter values for
//      GC9107_SET_VGL
#define VGL_N_075 0x40 // -7.5 V
#define VGL_N_085 0x41 // -8.5 V
#define VGL_N_095 0x42 // -9.5 V
#define VGL_N_100 0x43 // -10.0 V
#define VGL_N_105 0x44 // -10.5 V
#define VGL_N_110 0x45 // -11.0 V
#define VGL_N_120 0x46 // -12.0 V
#define VGL_N_130 0x47 // -13.0 V
// Parameter masks for
// GC9107_SET_VGH_VGL_CLK (VGH Divisor)
#define GC9107_VGH_CLK_DIV_2 0x00  // Clock divisor = 2 -> 6.0 Mhz
#define GC9107_VGH_CLK_DIV_3 0x10  // Clock divisor = 3 -> 4.0 Mhz
#define GC9107_VGH_CLK_DIV_4 0x20  // Clock divisor = 4 -> 3.0 Mhz
#define GC9107_VGH_CLK_DIV_5 0x30  // Clock divisor = 5 -> 2.4 Mhz
#define GC9107_VGH_CLK_DIV_6 0x40  // Clock divisor = 6 -> 2.0 Mhz
#define GC9107_VGH_CLK_DIV_7 0x50  // Clock divisor = 7 -> 1.7 Mhz
#define GC9107_VGH_CLK_DIV_8 0x60  // Clock divisor = 8 -> 1.5 Mhz
#define GC9107_VGH_CLK_DIV_9 0x70  // Clock divisor = 9 -> 1.3 Mhz
#define GC9107_VGH_CLK_DIV_10 0x80 // Clock divisor = 10 -> 1.2 Mhz
#define GC9107_VGH_CLK_DIV_12 0x90 // Clock divisor = 12 -> 1.0 Mhz
#define GC9107_VGH_CLK_DIV_15 0xA0 // Clock divisor = 15 -> 0.8 Mhz
#define GC9107_VGH_CLK_DIV_20 0xB0 // Clock divisor = 20 -> 0.6 Mhz
#define GC9107_VGH_CLK_DIV_24 0xC0 // Clock divisor = 24 -> 0.5 Mhz
#define GC9107_VGH_CLK_DIV_30 0xD0 // Clock divisor = 30 -> 0.4 Mhz
#define GC9107_VGH_CLK_DIV_40 0xE0 // Clock divisor = 40 -> 0.3 Mhz
#define GC9107_VGH_CLK_DIV_60 0xE0 // Clock divisor = 40 -> 0.2 Mhz
// Parameter masks for
// GC9107_SET_VGH_VGL_CLK (VGL Divisor)
#define GC9107_VGL_CLK_DIV_2 0x00  // Clock divisor = 2 -> 6.0 Mhz
#define GC9107_VGL_CLK_DIV_3 0x01  // Clock divisor = 3 -> 4.0 Mhz
#define GC9107_VGL_CLK_DIV_4 0x02  // Clock divisor = 4 -> 3.0 Mhz
#define GC9107_VGL_CLK_DIV_5 0x03  // Clock divisor = 5 -> 2.4 Mhz
#define GC9107_VGL_CLK_DIV_6 0x04  // Clock divisor = 6 -> 2.0 Mhz
#define GC9107_VGL_CLK_DIV_7 0x05  // Clock divisor = 7 -> 1.7 Mhz
#define GC9107_VGL_CLK_DIV_8 0x06  // Clock divisor = 8 -> 1.5 Mhz
#define GC9107_VGL_CLK_DIV_9 0x07  // Clock divisor = 9 -> 1.3 Mhz
#define GC9107_VGL_CLK_DIV_10 0x08 // Clock divisor = 10 -> 1.2 Mhz
#define GC9107_VGL_CLK_DIV_12 0x09 // Clock divisor = 12 -> 1.0 Mhz
#define GC9107_VGL_CLK_DIV_15 0x0A // Clock divisor = 15 -> 0.8 Mhz
#define GC9107_VGL_CLK_DIV_20 0x0B // Clock divisor = 20 -> 0.6 Mhz
#define GC9107_VGL_CLK_DIV_24 0x0C // Clock divisor = 24 -> 0.5 Mhz
#define GC9107_VGL_CLK_DIV_30 0x0D // Clock divisor = 30 -> 0.4 Mhz
#define GC9107_VGL_CLK_DIV_40 0x0E // Clock divisor = 40 -> 0.3 Mhz
#define GC9107_VGL_CLK_DIV_60 0x0E // Clock divisor = 40 -> 0.2 Mhz
