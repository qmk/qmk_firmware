// Copyright 2021 Christoph Rehmann (crehmann)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef OLED_ENABLE
#define OLED_DISPLAY_128X32
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
