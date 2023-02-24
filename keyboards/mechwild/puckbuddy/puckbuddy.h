// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define ___ KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    k00, k01, k02, k03,      k05,\
    k10,                     k15,\
    k20,                     k25,\
    k30,                     k35,\
         k31, k32, k33, k34      \
) { \
    { k00, k01, k05, k31 }, \
    { k10, k02, k15, k32 }, \
    { k20, k03, k25, k33 }, \
    { k30, ___, k35, k34 }  \
}

typedef union {
    uint32_t raw;
    struct {
        uint8_t dpi_config;
        int16_t dt_term_config;
    };
} keyboard_config_t;

extern keyboard_config_t keyboard_config;
extern uint16_t          dpi_array[];

enum keyboard_keycodes {
#ifdef VIA_ENABLE
    DPI_UP = USER00,
#else
    DPI_UP = SAFE_RANGE,
#endif
    DPI_DN,
    DPI_FINE,
    TAP_UP,
    TAP_DN,
    TAP_ON,
    TAP_OFF,
    TAP_TOG,
    NEW_SAFE_RANGE
};
