#pragma once

#include "progmem.h"

// Fundamental Commands
#define CONTRAST 0x81
#define DISPLAY_ALL_ON 0xA5
#define DISPLAY_ALL_ON_RESUME 0xA4
#define NORMAL_DISPLAY 0xA6
#define INVERT_DISPLAY 0xA7
#define DISPLAY_ON 0xAF
#define DISPLAY_OFF 0xAE
#define NOP 0xE3

// Scrolling Commands
#define ACTIVATE_SCROLL 0x2F
#define DEACTIVATE_SCROLL 0x2E
#define SCROLL_RIGHT 0x26
#define SCROLL_LEFT 0x27
#define SCROLL_RIGHT_UP 0x29
#define SCROLL_LEFT_UP 0x2A

// Addressing Setting Commands
#define MEMORY_MODE 0x20
#define COLUMN_ADDR 0x21
#define PAGE_ADDR 0x22
#define PAM_SETCOLUMN_LSB 0x00
#define PAM_SETCOLUMN_MSB 0x10
#define PAM_PAGE_ADDR 0xB0 // 0xb0 -- 0xb7

// Hardware Configuration Commands
#define DISPLAY_START_LINE 0x40
#define SEGMENT_REMAP 0xA0
#define SEGMENT_REMAP_INV 0xA1
#define MULTIPLEX_RATIO 0xA8
#define COM_SCAN_INC 0xC0
#define COM_SCAN_DEC 0xC8
#define DISPLAY_OFFSET 0xD3
#define COM_PINS 0xDA
#define COM_PINS_SEQ 0x02
#define COM_PINS_ALT 0x12
#define COM_PINS_SEQ_LR 0x22
#define COM_PINS_ALT_LR 0x32

// Timing & Driving Commands
#define DISPLAY_CLOCK 0xD5
#define PRE_CHARGE_PERIOD 0xD9
#define VCOM_DETECT 0xDB

// Advance Graphic Commands
#define FADE_BLINK 0x23
#define ENABLE_FADE 0x20
#define ENABLE_BLINK 0x30

// Charge Pump Commands
#define CHARGE_PUMP 0x8D

// Commands specific to the SH1107 chip
#define SH1107_DISPLAY_START_LINE 0xDC
#define SH1107_MEMORY_MODE_PAGE 0x20
#define SH1107_MEMORY_MODE_VERTICAL 0x21

// Misc defines
#ifndef OLED_BLOCK_COUNT
#    define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 8)
#endif
#ifndef OLED_BLOCK_SIZE
#    define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)
#endif

#define OLED_ALL_BLOCKS_MASK (((((OLED_BLOCK_TYPE)1 << (OLED_BLOCK_COUNT - 1)) - 1) << 1) | 1)

#define OLED_IC_HAS_HORIZONTAL_MODE (OLED_IC == OLED_IC_SSD1306)
#define OLED_IC_COM_PINS_ARE_COLUMNS (OLED_IC == OLED_IC_SH1107)

#ifndef OLED_COM_PIN_COUNT
#    if OLED_IC == OLED_IC_SSD1306
#        define OLED_COM_PIN_COUNT 64
#    elif OLED_IC == OLED_IC_SH1106
#        define OLED_COM_PIN_COUNT 64
#    elif OLED_IC == OLED_IC_SH1107
#        define OLED_COM_PIN_COUNT 128
#    else
#        error Invalid OLED_IC value
#    endif
#endif

#ifndef OLED_COM_PIN_OFFSET
#    define OLED_COM_PIN_OFFSET 0
#endif

// i2c defines
#define I2C_CMD 0x00
#define I2C_DATA 0x40
