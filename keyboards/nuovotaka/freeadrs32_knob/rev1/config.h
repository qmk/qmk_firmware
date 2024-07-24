// SPDX-FileCopyrightText: 2024 Takahiro Natsume ( @nuovotaka )
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* key matrix size */
#define MATRIX_ROWS 4     // 行数
#define MATRIX_COLS 5 * 2 // 列数 Duplex-Matrix

#define MATRIX_ROW_PINS { D2, D4, C6, D7} // 各行に割り当てるピン番号
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1 } // 各列に割り当てるピン番号
#define MATRIX_MASKED


#define ENCODER_PAD_A { E6, B5, B2 }
#define ENCODER_PAD_B { B4, B6, B3 }
#define ENCODER_MAP_KEY_DELAY 10

// RGB LED settings
#define WS2812_DI_PIN D3
#define RGBLIGHT_LED_COUNT 32

#ifdef RGBLIGHT_ENABLE
#    undef RGBLIGHT_EFFECT_BREATHING
#    undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#    undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    undef RGBLIGHT_EFFECT_SNAKE
#    undef RGBLIGHT_EFFECT_KNIGHT
#    undef RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    undef RGBLIGHT_EFFECT_RGB_TEST
#    undef RGBLIGHT_EFFECT_ALTERNATING
#    undef RGBLIGHT_EFFECT_TWINKLE
#endif

#ifdef RGBLIGHT_ENABLE
#ifndef RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL 120 // limitated for power consumption
#endif
#ifndef RGBLIGHT_VAL_STEP
#define RGBLIGHT_VAL_STEP 12
#endif
#ifndef RGBLIGHT_HUE_STEP
#define RGBLIGHT_HUE_STEP 17
#endif
#ifndef RGBLIGHT_SAT_STEP
#define RGBLIGHT_SAT_STEP 17
#endif
#endif

#ifndef OLED_FONT_H
#define OLED_FONT_H "keyboards/nuovotaka/lib/logofont/logofont.c"
#define OLED_FONT_START 32
#define OLED_FONT_END 175 // 0xAF
#endif

#if !defined(LAYER_STATE_8BIT) && !defined(LAYER_STATE_16BIT) && !defined(LAYER_STATE_32BIT)
#define LAYER_STATE_8BIT
#endif

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1

// To squeeze firmware size
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
