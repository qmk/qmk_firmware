// Copyright 2021 Ryan Skidmore (@ryanskidmore, rskeys@ryanskidmore.co.uk)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x7273 // rs
#define PRODUCT_ID   0x0064 // 100
#define DEVICE_VER   0x0001 // rev 1
#define MANUFACTURER ryanskidmore
#define PRODUCT      rsKeys100

/* Key Matrix Sizes */
#define MATRIX_ROWS 6
#define MATRIX_COLS 24

/* Rows */
#define ROW_A  D4
#define ROW_B  C6
#define ROW_C  D7
#define ROW_D  E6
#define ROW_E  B4
#define ROW_F  B5

/* Columns 0 - 20 (24 with dummy columns for shift registers) */
#define SHR_LATCH B2
#define SHR_CLOCK B3
#define SHR_DATA  B1
#define SHR_COLS { 0x000001, 0x000002, 0x000004, 0x000008, 0x000010, 0x000020, 0x000040, 0x000080, 0x000100, 0x000200, 0x000400, 0x000800, 0x001000, 0x002000, 0x004000, 0x008000, 0x010000, 0x020000, 0x040000, 0x080000, 0x100000, 0x200000, 0x400000, 0x800000 }

/* The shift registers on the matrix PCB output a signal on each column, which passes through the
 * switch and a diode towards the row. The row is then connected to the AVR as an input. This means
 * the diode direction is COL(umn) to ROW */
#define DIODE_DIRECTION COL2ROW

/* RGB Data Pin */
#define RGB_DI_PIN C7
/* The number of RGB LEDs connected */
#define DRIVER_LED_TOTAL 118
/* Set the maximum brightness to 110 to avoid going over 500 mA.
 * At full brightness with all three indicator LEDs on, the power draw is about 450 mA. */
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 110
/* Enable framebuffer effects */
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
/* Enable the cycle left right animation and set it as the startup mode */
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Set the max power consumption for the keyboard, which is 500 mA. */
#define USB_MAX_POWER_CONSUMPTION 500

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
#define FORCE_NKRO
