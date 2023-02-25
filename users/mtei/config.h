// Copyright (c) 2022 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later

// clang-format off

#pragma once

// Selection of RGBLIGHT MODE to use.
#undef RGBLIGHT_EFFECT_BREATHING
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_TWINKLE

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
#if (defined(KEYBOARD_helix_rev3_5rows) || defined(KEYBOARD_helix_rev2)) && !defined(SWITCH_MATRIX_INPUT_0)

/* Helix (Pro Micro) ******************
                     ====
                +-------====------+
                | D3/TXO      RAW |
                | D2/RXI      GND |
                | GND         RST |
                | GND         Vcc |
   DEBUG_MSCAN  | D1/SDA       F4 | COL_0
   DEBUG_MDELAY | D0/SCL       F5 | COL_1
          ROW_0 | D4           F6 | COL_2
          ROW_1 | C6           F7 | COL_3
          ROW_2 | D7       SCK/B1 | COL_4
          ROW_3 | E6      MISO/B3 | COL_5
          ROW_4 | B4      MOSI/B2 | COL_6
   DEBUG_READCOL| B5           B6 |
(debug_config.h)+-----------------+
***************************************/

 /* #define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 } */
#    define SWITCH_MATRIX_INPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (F0, 0xf0, MCU_GPIO),                              \
      (B0, 0x0e, MCU_GPIO) ),                            \
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (0, 0x20, 0x02), \
      (0, 0x40, 0x04), \
      (0, 0x80, 0x08), \
      (1, 0x02, 0x10), \
      (1, 0x08, 0x20), \
      (1, 0x04, 0x40) )

 /* #define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 } */
#    define SWITCH_MATRIX_OUTPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (D0, 0x90, MCU_GPIO), \
      (C0, 0x40, MCU_GPIO), \
      (E0, 0x40, MCU_GPIO), \
      (B0, 0x10, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (1, 0x40, 0x02), \
      (0, 0x80, 0x04), \
      (2, 0x40, 0x08), \
      (3, 0x10, 0x10) )

#endif // KEYBOARD_helix_rev3_5rows || KEYBOARD_helix_rev2

#ifdef DEBUG_CONFIG
#  include "debug_config.h"
#endif
