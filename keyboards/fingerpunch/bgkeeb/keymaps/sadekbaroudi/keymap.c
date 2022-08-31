/* Copyright 2021 Sadek Baroudi
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

#include "sadekbaroudi.h"
#include QMK_KEYBOARD_H

/*
 * The `LAYOUT_bgkeeb_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg ALPHA_ALT, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

// Note: changed the thumb keys from the following, testing out a new layout:
//                             KC_DEL, LT(_NAVIGATION,KC_ENT), LT(_FUNCTION,KC_TAB),           LT(_FUNCTION,KC_BSPC), LT(_SYMBOLS,KC_SPACE), KC_QUOT "\"
//                                            _______, KC_BSPC, LT(_NAVIGATION,KC_ENT),           LT(_SYMBOLS,KC_SPACE), KC_QUOT, _______ "\"

// clang-format off
#define LAYOUT_bgkeeb_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, \
              K33, K34, K35, K36, K37, K38 \
  ) \
  LAYOUT_wrapper( \
        K01,             K02,            K03,            LT(_FUNCTION, K04),  K05,            K06,                 LT(_FUNCTION, K07), K08,              K09,            K0A, \
        LCTL_T(K11),     LGUI_T(K12),    LALT_T(K13),    LSFT_T(K14),         K15,            LT(_MOUSE, K16),     RSFT_T(K17),        RALT_T(K18),      RGUI_T(K19),    RCTL_T(K1A), \
        K21,             K22,            K23,            K24,                 K25,            K26,                 K27,                K28,              K29,            K2A, \
                         KC_MUTE,        K33,            LT(_NAVIGATION,K34), LT(_FUNCTION,K35), LT(_MEDIA,K36),   LT(_SYMBOLS,K37),   K38,              LCTL(KC_BSPC) \
    )

/* Re-pass though to allow templates to be used */
#define LAYOUT_bgkeeb_base_wrapper(...)       LAYOUT_bgkeeb_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_ALPHA_ALT] = LAYOUT_bgkeeb_base_wrapper(
        _________________ALPHA_ALT_L1_________________, _________________ALPHA_ALT_R1_________________,
        _________________ALPHA_ALT_L2_________________, _________________ALPHA_ALT_R2_________________,
        _________________ALPHA_ALT_L3_________________, _________________ALPHA_ALT_R3_________________,
                                             __ALPHA_ALT_THUMBS_6__
    ),

    [_ALPHA] = LAYOUT_bgkeeb_base_wrapper(
        __________________ALPHA_L1____________________, __________________ALPHA_R1____________________,
        __________________ALPHA_L2____________________, __________________ALPHA_R2____________________,
        __________________ALPHA_L3____________________, __________________ALPHA_R3____________________,
                                              __ALPHA_THUMBS_6__
    ),

    [_NAVIGATION] = LAYOUT_wrapper(
        ________________NAVIGATION_1_______________, _________________NUMPAD_1__________________,
        ________________NAVIGATION_2_______________, _________________NUMPAD_2__________________,
        ________________NAVIGATION_3_______________, _________________NUMPAD_3__________________,
                  _______, _______, _______, KC_TAB, KC_BSPC, KC_SPACE, KC_DOT, _______
    ),

    [_SYMBOLS] = LAYOUT_wrapper(
        ________________SYMBOLS_L1_________________, ________________SYMBOLS_R1_________________,
        ________________SYMBOLS_L2_________________, ________________SYMBOLS_R2_________________,
        ________________SYMBOLS_L3_________________, ________________SYMBOLS_R3_________________,
                   _______, _______, KC_ENT, KC_DEL, KC_BSPC, _______, _______, _______
    ),

    [_FUNCTION] = LAYOUT_wrapper(
        ________________SHIFTNAV_1_________________, ________________FUNCTION_1_________________,
        ________________SHIFTNAV_2_________________, ________________FUNCTION_2_________________,
        ________________SHIFTNAV_3_________________, ________________FUNCTION_3_________________,
                _______, _______, _______, _______, N_DEL_LINE, KC_SPACE, _______, _______
    ),

    [_MEDIA] = LAYOUT_wrapper(
        ___________________RGB_1___________________, _________________MACROS_1__________________,
        ___________________RGB_2___________________, _________________MACROS_2__________________,
        ___________________RGB_3___________________, _________________MACROS_3__________________,
                 _______, _______, _______, _______, _______, _______, _______, _______
    ),
    
    [_MOUSE] = LAYOUT_wrapper(
        __________________MOUSE_1__________________, ___________________BLANK___________________,
        __________________MOUSE_2__________________, ___________________BLANK___________________,
        __________________MOUSE_3__________________, ___________________BLANK___________________,
           _______, _______, KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN3, KC_MS_BTN2, _______, _______
    )

};
