// Copyright 2024 Fernando Birra

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter GC9107 command opcodes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define GC9107_GET_ID_INFO 0x04             // Get ID information
#define GC9107_GET_STATUS 0x09              // Get status
#define GC9107_GET_POWER_MODE 0x0A          // Get power mode
#define GC9107_GET_MADCTL 0x0B              // Get MADCTL
#define GC9107_GET_PIXEL_FMT 0x0C           // Get pixel format
#define GC9107_GET_IMAGE_FMT 0x0D           // Get image format
#define GC9107_GET_SIGNAL_MODE 0x0E         // Get signal mode
#define GC9107_GET_DIAG_RESULT 0x0F         // Get self-diagnostic results
#define GC9107_CMD_SLEEP_ON 0x10            // Enter sleep mode
#define GC9107_CMD_SLEEP_OFF 0x11           // Exit sleep mode
#define GC9107_CMD_PARTIAL_ON 0x12          // Enter partial mode
#define GC9107_CMD_PARTIAL_OFF 0x13         // Exit partial mode
#define GC9107_CMD_INVERT_OFF 0x20          // Exit inverted mode
#define GC9107_CMD_INVERT_ON 0x21           // Enter inverted mode
#define GC9107_CMD_DISPLAY_OFF 0x28         // Disable display
#define GC9107_CMD_DISPLAY_ON 0x29          // Enable display
#define GC9107_SET_COL_ADDR 0x2A            // Set column address
#define GC9107_SET_COL_ADDR 0x2A            // Set column address (MSB(StartCol),LSB(StartCol),MSB(EndCol),LSB(EndCol)
#define GC9107_SET_ROW_ADDR 0x2B            // Set row address (MSB(StartRow),LSB(StartRow),MSB(EndRow),LSB(EndRow)
#define GC9107_SET_MEM 0x2C                 // Set (write) memory
#define GC9107_SET_PARTIAL_AREA 0x30        // Set partial area (MSB(StartRow),LSB(StartRow),MSB(EndRow),LSB(EndRow)
#define GC9107_SET_VSCROLL 0x33             // Set vertical scroll MSB(TFA),LSB(TFA),MSB(VSA),LSB(VSA),MSB(BFA),LSB(BFA)
#define GC9107_CMD_TEARING_OFF 0x34         // Tearing line OFF
#define GC9107_CMD_TEARING_ON 0x35          // Tearing line ON
#define GC9107_SET_MEM_ACS_CTL 0x36         // Set mem access ctl
#define GC9107_SET_VSCROLL_ADDR 0x37        // Set vscroll start addr
#define GC9107_CMD_IDLE_OFF 0x38            // Exit idle mode
#define GC9107_CMD_IDLE_ON 0x39             // Enter idle mode
#define GC9107_SET_PIXEL_FORMAT 0x3A        // Set pixel format
//      Parameter values for 
//      GC9107_SET_PIXEL_FORMAT
#       define PIXEL_FORMAT_12_BPP 0x01             // 12 bits per pixel
#       define PIXEL_FORMAT_16_BPP 0x05             // 16 bits per pixel
#       define PIXEL_FORMAT_18_BPP 0x06             // 18 bits per pixel
#define GC9107_SET_TEAR_SCANLINE 0x44       // Set tearing scanline (ScanLine[7:0])
#define GC9107_GET_TEAR_SCANLINE 0x45       // Get tearing scanline (ScanLine[7:0])
#define GC9107_SET_COMPLEMENT_RGB 0xAC      // Set complement Principle RGB
//      Parameter values for 
//      GC9107_SET_COMPLEMENT_RGB
#       define COMPLEMENT_WITH_0 0x00               // R0 <- B0 <- 0, except if data is FFh
#       define COMPLEMENT_WITH_1 0x40               // R0 <- B0 <- 1, except if data is 00h
#       define COMPLEMENT_WITH_MSB 0x80             // R0 <- R5, B0 <- B5
#       define COMPLEMENT_WITH_LSB 0xC0             // R0 <- B0 <- G0
#define GC9107_SET_BLANK_PORCH 0xAD         // Set blank porch control, 0;front_porch[6:0],0;back_porch[6:0]
#define GC9107_SET_FUNCTION_CTL1 0xB1       // Set access to AVDD_VCL_CLK and VGH_VGL_CLK commands
//      Parameter masks for
//      GC9107_SET_FUNCTION_CTL1
#       define ALLOW_AVDD_VCL_CLK 0b00001000        // Allow AVDD_VCL_CLK command
#define GC9107_SET_FUNCTION_CTL2 0xB2       // Set access to VGH, VGH control commands
//      Parameter masks for 
//      GC9107_SET_FUNCTION_CTL2
#       define ALLOW_SET_VGH 0b00000001             // Allow GC9107_SET_VGH
#       define ALLOW_SET_VGL 0b00000010             // Allow GC9107_SET_VGL
#       define ALLOW_SET_VGH_VGL_CLK 0b00000100     // Alloq GC9107_SET_VGH_VGL_CLK
#define GC9107_SET_FUNCTION_CTL3 0xB3       // Set access to Gamma control commands
//      Parameter masks for 
//      GC9107_SET_FUNCTION_CTL3
#       define ALLOW_SET_GAMMA1 0b00000001          // Allow GC9107_SET_GAMMA1
#       define ALLOW_SET_GAMMA2 0b00000010          // Allow GC9107_SET_GAMMA2
#define GC9107_SET_FUNCTION_CTL6 0xB6       // Set access to commands SET_FRAME_RATE, SET_COMPLEMENT_RGB and SET_BLANK_PORCH
//      Parameter mask for
//      GC9107_SET_FUNCTION_CTL6
#       define ALLOW_SET_FRAMERATE 0b000000001      // Allow GC9107_SET_FRAME_RATE
#       define ALLOW_SET_COMPLEMENT_RGB 0b000010000 // Allow GC9107_SET_COMPLEMENT_RGB
#       define ALLOW_SET_BLANK_PORCH 0b000100000    // Allow GFC9107_SET_BLANK_PORCH
#define GC9107_SET_DISPLAY_INVERSION 0xCB   // Set Display Inversion control
#define GC9107_SET_CUSTOM_ID_INFO 0xD3      // Set customize display id information
#define GC9107_GET_ID1 0xDA                 // Get ID1
#define GC9107_GET_ID2 0xDB                 // Get ID2
#define GC9107_GET_ID3 0xDC                 // Get ID3
#define GC9107_AVDD_VCL_CLK 0xE3            // AVDD_CLK
//      Parameter values for AVDD_CLK_AD part (Most significant nibble)
#       define AVDD_CLK_AD_2T 0x00
#       define AVDD_CLK_AD_3T 0x10
#       define AVDD_CLK_AD_4T 0x20
#       define AVDD_CLK_AD_5T 0x30
#       define AVDD_CLK_AD_6T 0x40
#       define AVDD_CLK_AD_7T 0x50
#       define AVDD_CLK_AD_8T 0x60
#       define AVDD_CLK_AD_9T 0x70
//      Parameter values for VCL_CLK_AD part (Least significant nibble)
#       define VCL_CLK_AD_2T 0x00
#       define VCL_CLK_AD_3T 0x01
#       define VCL_CLK_AD_4T 0x02
#       define VCL_CLK_AD_5T 0x03
#       define VCL_CLK_AD_6T 0x04
#       define VCL_CLK_AD_7T 0x05
#       define VCL_CLK_AD_8T 0x06
#       define VCL_CLK_AD_9T 0x07
#define GC9107_SET_VGH 0xE8                 // Set VGH
//      Parameter values for 
//      GC9107_SET_VGH
#       define VGH_P100 0x20                        // +10 V
#       define VGH_P110 0x21                        // +11 V
#       define VGH_P120 0x22                        // +12 V
#       define VGH_P130 0x23                        // +13 V
#       define VGH_P140 0x24                        // +14 V
#       define VGH_P150 0x25                        // +15 V
#define GC9107_SET_VGL 0xE9                 // Set VGL
//      Parameter values for
//      GC9107_SET_VGL
#       define VGL_N_075 0x40                       // -7.5 V
#       define VGL_N_085 0x41                       // -8.5 V
#       define VGL_N_095 0x42                       // -9.5 V
#       define VGL_N_100 0x43                       // -10.0 V
#       define VGL_N_105 0x44                       // -10.5 V
#       define VGL_N_110 0x45                       // -11.0 V
#       define VGL_N_120 0x46                       // -12.0 V
#       define VGL_N_130 0x47                       // -13.0 V
#define GC9107_SET_VGH_VGL_CLK 0xEA         // Set VGH and VGL clock divisors
// Parameter masks for 
// GC9107_SET_VGH_VGL_CLK (VGH Divisor)
#       define VGH_CLK_DIV_2 0x00                   // Clock divisor = 2 -> 6.0 Mhz
#       define VGH_CLK_DIV_3 0x10                   // Clock divisor = 3 -> 4.0 Mhz
#       define VGH_CLK_DIV_4 0x20                   // Clock divisor = 4 -> 3.0 Mhz
#       define VGH_CLK_DIV_5 0x30                   // Clock divisor = 5 -> 2.4 Mhz
#       define VGH_CLK_DIV_6 0x40                   // Clock divisor = 6 -> 2.0 Mhz
#       define VGH_CLK_DIV_7 0x50                   // Clock divisor = 7 -> 1.7 Mhz
#       define VGH_CLK_DIV_8 0x60                   // Clock divisor = 8 -> 1.5 Mhz
#       define VGH_CLK_DIV_9 0x70                   // Clock divisor = 9 -> 1.3 Mhz
#       define VGH_CLK_DIV_10 0x80                  // Clock divisor = 10 -> 1.2 Mhz
#       define VGH_CLK_DIV_12 0x90                  // Clock divisor = 12 -> 1.0 Mhz
#       define VGH_CLK_DIV_15 0xA0                  // Clock divisor = 15 -> 0.8 Mhz
#       define VGH_CLK_DIV_20 0xB0                  // Clock divisor = 20 -> 0.6 Mhz
#       define VGH_CLK_DIV_24 0xC0                  // Clock divisor = 24 -> 0.5 Mhz
#       define VGH_CLK_DIV_30 0xD0                  // Clock divisor = 30 -> 0.4 Mhz
#       define VGH_CLK_DIV_40 0xE0                  // Clock divisor = 40 -> 0.3 Mhz
#       define VGH_CLK_DIV_60 0xE0                  // Clock divisor = 40 -> 0.2 Mhz
// Parameter masks for 
// GC9107_SET_VGH_VGL_CLK (VGL Divisor)
#       define VGL_CLK_DIV_2 0x00                   // Clock divisor = 2 -> 6.0 Mhz
#       define VGL_CLK_DIV_3 0x01                   // Clock divisor = 3 -> 4.0 Mhz
#       define VGL_CLK_DIV_4 0x02                   // Clock divisor = 4 -> 3.0 Mhz
#       define VGL_CLK_DIV_5 0x03                   // Clock divisor = 5 -> 2.4 Mhz
#       define VGL_CLK_DIV_6 0x04                   // Clock divisor = 6 -> 2.0 Mhz
#       define VGL_CLK_DIV_7 0x05                   // Clock divisor = 7 -> 1.7 Mhz
#       define VGL_CLK_DIV_8 0x06                   // Clock divisor = 8 -> 1.5 Mhz
#       define VGL_CLK_DIV_9 0x07                   // Clock divisor = 9 -> 1.3 Mhz
#       define VGL_CLK_DIV_10 0x08                  // Clock divisor = 10 -> 1.2 Mhz
#       define VGL_CLK_DIV_12 0x09                  // Clock divisor = 12 -> 1.0 Mhz
#       define VGL_CLK_DIV_15 0x0A                  // Clock divisor = 15 -> 0.8 Mhz
#       define VGL_CLK_DIV_20 0x0B                  // Clock divisor = 20 -> 0.6 Mhz
#       define VGL_CLK_DIV_24 0x0C                  // Clock divisor = 24 -> 0.5 Mhz
#       define VGL_CLK_DIV_30 0x0D                  // Clock divisor = 30 -> 0.4 Mhz
#       define VGL_CLK_DIV_40 0x0E                  // Clock divisor = 40 -> 0.3 Mhz
#       define VGL_CLK_DIV_60 0x0E                  // Clock divisor = 40 -> 0.2 Mhz
#define GC9107_SET_GAMMA1 0xF0              // Set gamma 1
#define GC9107_SET_GAMMA2 0xF1              // Set gamma 2
#define GC9107_SET_INTER_REG_ENABLE1 0xFE   // Enable Inter Register 1
#define GC9107_SET_INTER_REG_ENABLE2 0xEF   // Enable Inter Register 2

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MADCTL Flags
#define GC9107_MADCTL_MY 0b10000000
#define GC9107_MADCTL_MX 0b01000000
#define GC9107_MADCTL_MV 0b00100000
#define GC9107_MADCTL_ML 0b00010000
#define GC9107_MADCTL_RGB 0b00000000
#define GC9107_MADCTL_BGR 0b00001000
#define GC9107_MADCTL_MH 0b00000100
