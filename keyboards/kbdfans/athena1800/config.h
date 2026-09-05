// Copyright 2026 Laszlo Toth (@laszloth)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define MATRIX_ROWS 14
#define MATRIX_COLS 8

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP14
#define SPI_MOSI_PIN GP15
#define SPI_MISO_PIN GP20 /* unused */

#define LCD_RST_PIN GP16
#define LCD_CS_PIN GP13
#define LCD_DC_PIN GP12
#define LCD_SPI_DIVISOR 4
#define LCD_SPI_MODE 0 /* GC9107 SPI mode 0 (CPOL=0, CPHA=0) */
#define LCD_WIDTH 128
#define LCD_HEIGHT 128
/*
 * Upright on this panel with upstream's gc9107 driver. (The vendor
 * firmware uses QP_ROTATION_0, but it ships its own custom gc9107
 * init/madctl sequence, so its rotation value is not directly
 * comparable.)
 */
#define LCD_ROTATION QP_ROTATION_180
#define LCD_OFFSET_X 2
#define LCD_OFFSET_Y 1
/* always on like vendor fw (QMK default times out at 30s) */
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0
