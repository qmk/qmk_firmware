// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgblight.h"

#define RGBLIGHT_RAINBOW_SWIRL_RANGE 255

extern rgblight_config_t rgblight_config;
extern rgb_led_t led[RGBLIGHT_LED_COUNT];

extern void sethsv(uint8_t hue, uint8_t sat, uint8_t val, rgb_led_t *led1);
