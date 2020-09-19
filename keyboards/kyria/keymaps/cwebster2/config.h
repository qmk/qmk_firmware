/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
  //#define RGBLIGHT_ANIMATIONS
  //#define RGBLIGHT_EFFECT_ALTERNATING
  #define RGBLIGHT_EFFECT_BREATHING
  //#define RGBLIGHT_EFFECT_CHRISTMAS
  #define RGBLIGHT_EFFECT_KNIGHT
  //#define RGBLIGHT_EFFECT_RAINBOW_MOOD
  //#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  //#define RGBLIGHT_EFFECT_RGB_TEST
  //#define RGBLIGHT_EFFECT_SNAKE
  //#define RGBLIGHT_EFFECT_STATIC_GRADIENT
  //#define RGBLIGHT_EFFECT_TWINKLE
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_SLEEP
  #define RGBLIGHT_LIMIT_VAL 128
#endif

#define TAPPING_TOGGLE 1
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT

#define AUTO_SHIFT_TIMEOUT 200
#define NO_AUTO_SHIFT_SPECIAL
#define NO_AUTO_SHIFT_ALPHA

#define EE_HANDS


/* Disable unused and unneeded features to reduce on firmware size */
#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif

#define LAYOUT_kc( \
    L00, L01, L02, L03, L04, L05,                     R05, R04, R03, R02, R01, R00, \
    L10, L11, L12, L13, L14, L15,                     R15, R14, R13, R12, R11, R10, \
    L20, L21, L22, L23, L24, L25, L26, L27, R27, R26, R25, R24, R23, R22, R21, R20, \
                   L33, L34, L35, L36, L37, R37, R36, R35, R34, R33 \
    ) \
    LAYOUT ( \
    KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05,                     KC_##R05, KC_##R04, KC_##R03, KC_##R02, KC_##R01, KC_##R00, \
    KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15,                     KC_##R15, KC_##R14, KC_##R13, KC_##R12, KC_##R11, KC_##R10, \
    KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25, KC_##L26, KC_##L27, KC_##R27, KC_##R26, KC_##R25, KC_##R24, KC_##R23, KC_##R22, KC_##R21, KC_##R20, \
                   KC_##L33, KC_##L34, KC_##L35, KC_##L36, KC_##L37, KC_##R37, KC_##R36, KC_##R35, KC_##R34, KC_##R33 \
    )
