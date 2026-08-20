// Copyright 2026 Connor Gallopo (@connorgallopo)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "pin_defs.h"

/* OLED: SSD1326 256x32, driven directly by the main MCU over I2C0
 * (PB0 SDA / PB1 SCL at AFIO mode 7, PD1 active-low RST). Driver at
 * ssd1326.c uses raw register writes — chibios-contrib has no HT32 I2C LLD. */

/* Orientation detect: stock firmware reads PA15 (pin idx 0x29) via
 * FUN_0000a0ec at Ghidra 0xa0ec. HIGH = regular, LOW = southpaw.
 * Exposed as `tenet_read_orientation()`. */

/* Keyboard-reserved EEPROM datablock: 16 bytes persistent OLED text plus
 * headroom for future state. */
#define EECONFIG_KB_DATA_SIZE 32

/* HT32 has no on-chip EEPROM. QMK uses a RAM-backed transient store, sized for
 * core eeconfig plus the keyboard data block and RGB matrix state. */
#define TRANSIENT_EEPROM_SIZE 1024

#define PERMISSIVE_HOLD

/* RGB Matrix: 76 LEDs across the mainboard (64) and daughterboard (12)
 * sub-MCUs. ws2812_custom.c mirrors stock's SPI1 sub-MCU command protocol. */
#define RGB_MATRIX_LED_COUNT 76
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_DEFAULT_VAL 100
#define RGB_MATRIX_SLEEP
