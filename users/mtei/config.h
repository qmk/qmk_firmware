// Copyright (c) 2022 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later

// clang-format off

#pragma once

// Selection of RGBLIGHT MODE to use.
#undef RGBLIGHT_ANIMATIONS
#undef RGBLIGHT_EFFECT_BREATHING
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING

#if defined(LED_ANIMATIONS)
#    if LED_ANIMATIONS_LEVEL > 1
#        define RGBLIGHT_EFFECT_BREATHING
#        define RGBLIGHT_EFFECT_RAINBOW_MOOD
#        define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#        define RGBLIGHT_EFFECT_SNAKE
//#        define RGBLIGHT_EFFECT_KNIGHT
#        define RGBLIGHT_EFFECT_CHRISTMAS
#        define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#        define RGBLIGHT_EFFECT_RGB_TEST
//#        define RGBLIGHT_EFFECT_ALTERNATING
#    else
#        define RGBLIGHT_EFFECT_BREATHING
#        define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#        define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#        define RGBLIGHT_EFFECT_SNAKE
//#        define RGBLIGHT_EFFECT_KNIGHT
//#        define RGBLIGHT_EFFECT_CHRISTMAS
#        define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#        define RGBLIGHT_EFFECT_RGB_TEST
//#        define RGBLIGHT_EFFECT_ALTERNATING
#        endif
#endif

// clang-format off
#ifdef KEYBOARD_helix_rev3_5rows

 /* #define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 } */
#define SWITCH_MATRIX_INPUT_0 \
    /* ( ( <port>, <mask> [, <dev>] ), ... ) */ \
    ( (F0, 0xf0), \
      (B0, 0x0e) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (0, 0x20, 0x02), \
      (0, 0x40, 0x04), \
      (0, 0x80, 0x08), \
      (1, 0x02, 0x10), \
      (1, 0x08, 0x20), \
      (1, 0x04, 0x40) )

 /* #define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 } */
#define SWITCH_MATRIX_OUTPUT_0 \
    /* ( ( <port>, <mask> [, <dev>] ), ... ) */ \
    ( (D0, 0x90), \
      (C0, 0x40), \
      (E0, 0x40), \
      (B0, 0x10) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (1, 0x40, 0x02), \
      (0, 0x80, 0x04), \
      (2, 0x40, 0x08), \
      (3, 0x10, 0x10) )

#ifdef DIFF_HAND
#    undef SPLIT_HAND_MATRIX_GRID
#    undef SPLIT_HAND_MATRIX_GRID_LOW_IS_RIGHT

 /* #define MATRIX_COL_PINS_RIGHT { F4, F5, F6, F7, B3, B1, B2 } */
#define SWITCH_MATRIX_INPUT_1 \
    /* ( ( <port>, <mask> [, <dev>] ), ... ) */ \
    ( (F0, 0xf0), \
      (B0, 0x0e) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (0, 0x20, 0x02), \
      (0, 0x40, 0x04), \
      (0, 0x80, 0x08), \
      (1, 0x08, 0x10), \
      (1, 0x02, 0x20), \
      (1, 0x04, 0x40) )

 /* #define MATRIX_ROW_PINS_RIGHT { D4, C6, E6, D7, B4 } */
#define SWITCH_MATRIX_OUTPUT_1 \
    /* ( ( <port>, <mask> [, <dev>] ), ... ) */ \
    ( (D0, 0x90), \
      (C0, 0x40), \
      (E0, 0x40), \
      (B0, 0x10) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (1, 0x40, 0x02), \
      (2, 0x40, 0x04), \
      (0, 0x80, 0x08), \
      (3, 0x10, 0x10) )
#endif // DIFF_HAND

#endif // KEYBOARD_helix_rev3_5rows

#ifdef DEBUG_CONFIG
#  include "debug_config.h"
#endif
