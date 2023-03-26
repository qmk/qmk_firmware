// Copyright 2021 Christoph Rehmann (crehmann)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// wiring
#define MATRIX_ROW_PINS \
    { F4, F5, F6, F7 }
#define MATRIX_COL_PINS \
    { B1, B3, B2, B6, B5, B4}

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#ifdef OLED_ENABLE
#define OLED_DISPLAY_128X32
#define SPLIT_OLED_ENABLE
#endif

#ifdef PS2_DRIVER_INTERRUPT
#define PS2_CLOCK_PIN   E6
#define PS2_DATA_PIN    D7

#define PS2_INT_INIT()  do {    \
    EICRB |= ((1<<ISC61) |      \
              (0<<ISC60));      \
    } while (0)
#define PS2_INT_ON()  do {      \
     EIMSK |= (1<<INT6);        \
} while (0)
#define PS2_INT_OFF() do {      \
    EIMSK &= ~(1<<INT6);        \
} while (0)
#define PS2_INT_VECT   INT6_vect
#define PS2_MOUSE_ROTATE 270 /* Compensate for East-facing device orientation. */
#endif
