/* Copyright 2022 Johannes Schneider (@JohSchneider) */
/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    No-oNe
#define PRODUCT         YaMseK
//#define DESCRIPTION     Yet-another-Modular-split-ergonomic-Keyboard

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6
/* colum major:
   first four rows are on the lefthand side, behind a port expander
   next four rows are on the rightnad side, connected to the single MCU running this keyboard
*/

// black mark on diode facing columns
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
