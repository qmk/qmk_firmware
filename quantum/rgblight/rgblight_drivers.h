// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    void (*init)(void);
    void (*set_color)(int index, uint8_t red, uint8_t green, uint8_t blue);
    void (*set_color_all)(uint8_t red, uint8_t green, uint8_t blue);
    void (*flush)(void);
    /* Optional: toggle the chain's VCC-enable rail. NULL when not supported. */
    void (*set_power)(bool on);
} rgblight_driver_t;

extern const rgblight_driver_t rgblight_driver;
