// Copyright 2023 NuPhy
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>
#include "color.h"

// Generic side LED driver interface
// This abstracts the underlying LED driver (WS2812, IS31FL3733, etc.)

typedef struct {
    void (*init)(void);
    void (*set_leds)(rgb_led_t *ledarray, uint16_t leds);
    void (*flush)(void);
} side_driver_t;

// Get the appropriate driver for the current keyboard
// This is implemented per-keyboard or uses weak defaults
__attribute__((weak)) const side_driver_t *get_side_driver(void);
