#pragma once

#include "config_common.h"

// USB Device descriptor
#define VENDOR_ID       0x4158  // 'AX'
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    Aahil
#define PRODUCT         CYBR-X
#define DESCRIPTION     4x4 Macropad with MCP23017, Encoders & OLED

// Keyboard matrix
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

// External matrix via I2C
#define MATRIX_ROW_PINS {}
#define MATRIX_COL_PINS {}
#define DIODE_DIRECTION ROW2COL

// Use MCP23017 I2C Expander
#define MCP23017
#define MCP23017_ADDRESS 0x20  // All address pins grounded

#define MCP23017_ROWS { GPB0, GPB1, GPB2, GPB3 }
#define MCP23017_COLS { GPB4, GPB5, GPB6, GPA0 }

// Rotary Encoder configuration
#define ENCODERS 2
#define ENCODERS_PAD_A { GPA1, GPA4 }
#define ENCODERS_PAD_B { GPA2, GPA5 }
#define ENCODERS_PAD_A_MCP23017
#define ENCODERS_PAD_B_MCP23017

// Encoder button pins
#define ENCODER_BUTTONS { GPA3, GPA6 }
#define ENCODER_BUTTONS_MCP23017

// OLED settings
#define OLED_DISPLAY_128X32
#define I2C1_SCL_PIN GP1
#define I2C1_SDA_PIN GP0

// RP2040 specific
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
