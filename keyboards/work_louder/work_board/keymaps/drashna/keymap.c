/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "drashna.h"

#define PLNK_1 SP_LWER
#define PLNK_2 BK_LWER
#define PLNK_3 DL_RAIS
#define PLNK_4 ET_RAIS

/*
 * The `LAYOUT_ortho_4x12_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */
// clang-format off
#define LAYOUT_wrapper(...)       LAYOUT(__VA_ARGS__)
#define LAYOUT_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
    KC_ESC,  K01,    K02,     K03,      K04,     K05,     K06,     K07,     K08,     K09,     K0A,     KC_DEL, KC_MUTE, \
    LALT_T(KC_TAB), K11, K12, K13,      K14,     K15,     K16,     K17,     K18,     K19,     K1A, RALT_T(K1B), \
    KC_MLSF, CTL_T(K21), K22, K23,      K24,     K25,     K26,     K27,     K28,     K29, RCTL_T(K2A), KC_ENT,  \
    OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, PLNK_1,  PLNK_2,  PLNK_3,  PLNK_4,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
  )
#define LAYOUT_base_wrapper(...)       LAYOUT_base(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT_LAYER_1] = LAYOUT_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_DEFAULT_LAYER_2] = LAYOUT_base_wrapper(
        ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________,
        ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________,
        ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________
    ),
    [_DEFAULT_LAYER_3] = LAYOUT_base_wrapper(
        _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
        _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
    ),

    [_DEFAULT_LAYER_4] = LAYOUT_base_wrapper(
        _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
        _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
        _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
    ),

  [_LOWER] = LAYOUT_wrapper(
    KC_TILD, _________________LOWER_L1__________________, _________________LOWER_R1__________________, KC_BSPC, _______,
    KC_DEL,  _________________LOWER_L2__________________, _________________LOWER_R2__________________, KC_PIPE,
    _______, _________________LOWER_L3__________________, _________________LOWER_R3__________________, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_RAISE] = LAYOUT_wrapper(
    KC_GRV,  _________________RAISE_L1__________________, _________________RAISE_R1__________________, KC_BSPC, _______,
    KC_DEL,  _________________RAISE_L2__________________, _________________RAISE_R2__________________, KC_BSLS,
    _______, _________________RAISE_L3__________________, _________________RAISE_R3__________________, _______,
    _______, _______, _______, _______, _______, _______, _______, _________________RAISE_R3__________________
  ),

  [_ADJUST] = LAYOUT_wrapper(
    QK_MAKE, _________________ADJUST_L1_________________, _________________ADJUST_R1_________________, QK_BOOT, _______,
    VRSN,    _________________ADJUST_L2_________________, _________________ADJUST_R2_________________, EE_CLR,
    _______, _________________ADJUST_L3_________________, _________________ADJUST_R3_________________, RGB_IDL,
    KEYLOCK, _______, _______, _______, _______, KC_NUKE, _______, _______, _______, _______, _______, TG_MODS
  )

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_DEFAULT_LAYER_1] = { { KC_DOWN, KC_UP   } },
    [_DEFAULT_LAYER_2] = { { _______, _______ } },
    [_DEFAULT_LAYER_3] = { { _______, _______ } },
    [_DEFAULT_LAYER_4] = { { _______, _______ } },
    [_GAMEPAD]         = { { _______, _______ } },
    [_DIABLO]          = { { _______, _______ } },
    [_MOUSE]           = { { KC_WH_D, KC_WH_U } },
    [_MEDIA]           = { { _______, _______ } },
    [_RAISE]           = { { KC_VOLD, KC_VOLU } },
    [_LOWER]           = { { RGB_MOD, RGB_RMOD} },
    [_ADJUST]          = { { CK_DOWN, CK_UP   } },
};
// clang-format on
#endif

bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
    uint8_t this_mod = get_mods();
    led_t   this_led = host_keyboard_led_state();
    uint8_t this_osm = get_oneshot_mods();
#define THUMB_LED                                   6
#define RGB_MATRIX_INDICATOR_SET_COLOR_wrapper(...) RGB_MATRIX_INDICATOR_SET_COLOR(__VA_ARGS__)

    if (get_keyboard_lock()) {
        RGB_MATRIX_INDICATOR_SET_COLOR_wrapper(THUMB_LED, RGB_OFF);
    } else {
        switch (get_highest_layer(default_layer_state)) {
            case _DEFAULT_LAYER_1:
                RGB_MATRIX_INDICATOR_SET_COLOR_wrapper(THUMB_LED, DEFAULT_LAYER_1_RGB);
                break;
            case _DEFAULT_LAYER_2:
                RGB_MATRIX_INDICATOR_SET_COLOR_wrapper(THUMB_LED, DEFAULT_LAYER_2_RGB);
                break;
            case _DEFAULT_LAYER_3:
                RGB_MATRIX_INDICATOR_SET_COLOR_wrapper(THUMB_LED, DEFAULT_LAYER_3_RGB);
                break;
            case _DEFAULT_LAYER_4:
                RGB_MATRIX_INDICATOR_SET_COLOR_wrapper(THUMB_LED, DEFAULT_LAYER_4_RGB);
                break;
        }
    }

    if ((this_mod | this_osm) & MOD_MASK_SHIFT || this_led.caps_lock) {
        if (!layer_state_is(_ADJUST)) {
            RGB_MATRIX_INDICATOR_SET_COLOR(12, 0x00, 0xFF, 0x00);
            RGB_MATRIX_INDICATOR_SET_COLOR(13, 0x00, 0xFF, 0x00);
        }
        RGB_MATRIX_INDICATOR_SET_COLOR(24, 0x00, 0xFF, 0x00);
    }
    if ((this_mod | this_osm) & MOD_MASK_CTRL) {
        RGB_MATRIX_INDICATOR_SET_COLOR(11, 0xFF, 0x00, 0x00);
        RGB_MATRIX_INDICATOR_SET_COLOR(23, 0xFF, 0x00, 0x00);
        RGB_MATRIX_INDICATOR_SET_COLOR(14, 0xFF, 0x00, 0x00);
    }
    if ((this_mod | this_osm) & MOD_MASK_GUI) {
        RGB_MATRIX_INDICATOR_SET_COLOR(9, 0xFF, 0xD9, 0x00);
    }
    if ((this_mod | this_osm) & MOD_MASK_ALT) {
        RGB_MATRIX_INDICATOR_SET_COLOR(10, 0x00, 0x00, 0xFF);
        RGB_MATRIX_INDICATOR_SET_COLOR(25, 0x00, 0x00, 0xFF);
        RGB_MATRIX_INDICATOR_SET_COLOR(36, 0x00, 0x00, 0xFF);
    }
    if (layer_state_is(_LOWER)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(7, 0x00, 0xFF, 0x00);
        RGB_MATRIX_INDICATOR_SET_COLOR(8, 0x00, 0xFF, 0x00);
    }
    if (layer_state_is(_RAISE)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(4, 0xFF, 0xFF, 0x00);
        RGB_MATRIX_INDICATOR_SET_COLOR(5, 0xFF, 0xFF, 0x00);
    }

    return true;
}
