// Copyright 2024 Sinisha Stojchevski (@sini6a)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Hold the ESC key while plugging in the keyboard to enter bootloader mode */
#define BOOTMAGIC_KEY_SALT KC_NO    // No modifier needed
#define BOOTMAGIC_KEY_SALT2 KC_NO   // No second modifier needed
#define BOOTMAGIC_KEY_BOOT KC_ESCAPE   // Press 'ESC' key

/* RGB Configuration for SK6812 MINI-E LED */
#define WS2812_DI_PIN B7
#define RGBLIGHT_LED_COUNT 54

#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE

#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL
#define RGBLIGHT_LIMIT_VAL 120
