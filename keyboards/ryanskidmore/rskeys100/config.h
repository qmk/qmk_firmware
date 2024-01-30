// Copyright 2021 Ryan Skidmore (@ryanskidmore, rskeys@ryanskidmore.co.uk)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

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

/* The number of RGB LEDs connected */
#define RGB_MATRIX_LED_COUNT 105

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
