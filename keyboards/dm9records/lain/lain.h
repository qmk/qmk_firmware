// Copyright 2022 Takuya Urakawa @hsgw (dm9records.com, 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

typedef union {
    uint32_t raw;
    struct {
        bool led_enabled : 1;
    };
} keyboard_config_t;

extern keyboard_config_t lain_config;

void lain_set_led(uint8_t no, bool flag);
void lain_enable_leds(bool flag);
void lain_enable_leds_toggle(void);

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
// clang-format off
#define LAYOUT( \
    k01,k02,k03,k04,k05,k06,k07,    k08,k09,k10,k11,k12,k13, \
    k14,k15,k16,k17,k18,k19,k20,    k21,k22,k23,k24,k25,k26, \
    k27,k28,k29,k30,k31,k32,        k33,k34,k35,k36,k37,k38, \
            k39,k40,k41,k42,k43,    k44,k45,k46,k47,k48,k49) \
    { \
        {k01,  k02,  k03,k04,k05,k06,k07,    k08,k09,k10,k11,k12,k13}, \
        {k14,  k15,  k16,k17,k18,k19,k20,    k21,k22,k23,k24,k25,k26}, \
        {k27,  k28,  k29,k30,k31,k32,KC_NO,  k33,k34,k35,k36,k37,k38}, \
        {KC_NO,k39,  k40,k41,k42,k43,KC_NO,  k44,k45,k46,k47,k48,k49} \
    }
// clang-format on
