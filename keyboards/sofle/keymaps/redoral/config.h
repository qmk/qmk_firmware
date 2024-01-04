/* Copyright 2023 Red Oral
 * Based on the via keymap and modified it to my own keymap and OLED display preference
 * Displays layer and capslock information on main oled, Witcher signs on the offhand oled
 *
 * By default left side is selected as master,
 * see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
 * for more options.
 */

#pragma once

#if defined(KEYBOARD_sofle_rev1)
//   Experimental 1000hz polling (might be default?)
#    define USB_POLLING_INTERVAL_MS 1
//   Cold boot fix
#    define SPLIT_USB_TIMEOUT 10000
#    define SPLIT_USB_TIMEOUT_POLL 10
//   Add RGB underglow and top facing lighting
#    define WS2812_DI_PIN D3
#    define RGBLED_NUM 72
#    define RGBLED_SPLIT \
        { 36, 36 }
#    ifdef RGB_MATRIX_ENABLE
#        define RGB_MATRIX_LED_COUNT RGBLED_NUM
#        define RGB_MATRIX_SPLIT RGBLED_SPLIT
#        define SPLIT_TRANSPORT_MIRROR
#    else
#        define RGBLIGHT_EFFECT_BREATHING
#        define RGBLIGHT_EFFECT_RAINBOW_MOOD
#        define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#        define RGBLIGHT_EFFECT_SNAKE
#        define RGBLIGHT_EFFECT_KNIGHT
#        define RGBLIGHT_EFFECT_CHRISTMAS
#        define RGBLIGHT_EFFECT_STATIC_GRADIENT
#        define RGBLIGHT_EFFECT_RGB_TEST
#        define RGBLIGHT_EFFECT_ALTERNATING
#        define RGBLIGHT_EFFECT_TWINKLE
#        define RGBLIGHT_LIMIT_VAL 120
#        define RGBLIGHT_HUE_STEP 10
#        define RGBLIGHT_SAT_STEP 17
#        define RGBLIGHT_VAL_STEP 17
#    endif
#endif
