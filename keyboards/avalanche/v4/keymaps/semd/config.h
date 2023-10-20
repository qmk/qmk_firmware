// Copyright 2022 Will Winder (@winder)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define USE_SERIAL
#define EE_HANDS
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2000
#define SPLIT_USB_TIMEOUT_POLL 3

#define RGBLIGHT_LAYERS

#undef RGBLIGHT_EFFECT_BREATHING
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_TWINKLE
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD


#ifdef OLED_ENABLE
    #undef OLED_TIMEOUT
    #undef OLED_FONT_H
    #define OLED_TIMEOUT 15000
    #define OLED_FONT_H "keyboards/avalanche/v4/keymaps/semd/glcdfont.c"
#endif

#define CAPS_WORD_INVERT_ON_SHIFT

// saving space
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
