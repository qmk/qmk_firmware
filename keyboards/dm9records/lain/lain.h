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
