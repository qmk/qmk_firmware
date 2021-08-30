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

enum crkbd_keycodes { RGBRST = NEW_SAFE_RANGE };

/*
 * The `LAYOUT_crkbd_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

#ifdef CONVERT_TO_PROTON_C
#    define MID_TMB ET_RAIS
#else
#    define MID_TMB KC_ENT
#endif

// clang-format off
#define LAYOUT_split_3x6_3_wrapper(...)      LAYOUT_split_3x6_3(__VA_ARGS__)
#define LAYOUT_split_3x6_3_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_split_3x6_3_wrapper( \
    KC_ESC,  K01,    K02,     K03,      K04,     K05,                        K06,     K07,     K08,     K09,     K0A,     KC_MINS, \
    ALT_T(KC_TAB), K11,  K12, K13,      K14,     K15,                        K16,     K17,     K18,     K19,     K1A, RALT_T(K1B), \
    OS_LSFT, CTL_T(K21), K22, K23,      K24,     K25,                        K26,     K27,     K28,     K29, RCTL_T(K2A), OS_RSFT, \
                                        OS_LGUI, KC_SPC,  BK_LWER, DL_RAIS,  MID_TMB,  OS_RGUI                                      \
  )
#define LAYOUT_base_wrapper(...)       LAYOUT_split_3x6_3_base(__VA_ARGS__)

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

  [_LOWER] = LAYOUT_split_3x6_3_wrapper(
    KC_F11,  _________________LOWER_L1__________________,                    _________________LOWER_R1__________________, KC_F11,
    KC_F12,  _________________LOWER_L2__________________,                    _________________LOWER_R2__________________, KC_PIPE,
    _______, _________________LOWER_L3__________________,                    _________________LOWER_R3__________________, _______,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_RAISE] = LAYOUT_split_3x6_3_wrapper( \
    _______, _________________RAISE_L1__________________,                    _________________RAISE_R1__________________, _______,
    _______, _________________RAISE_L2__________________,                    _________________RAISE_R2__________________, KC_BSLS,
    _______, _________________RAISE_L3__________________,                    _________________RAISE_R3__________________, _______,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_split_3x6_3_wrapper( \
    KC_MAKE, _________________ADJUST_L1_________________,                    _________________ADJUST_R1_________________, KC_RESET,
    VRSN,    _________________ADJUST_L2_________________,                    _________________ADJUST_R2_________________, EEP_RST,
    MG_NKRO, _________________ADJUST_L3_________________,                    _________________ADJUST_R3_________________, RGB_IDL,
                                     HPT_TOG, KC_NUKE, _______,        _______, TG_MODS, HPT_FBK
  )
};
// clang-format on

#ifdef OLED_ENABLE
oled_rotation_t oled_init_keymap(oled_rotation_t rotation) { return OLED_ROTATION_270; }
#endif

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_T(KC_A):
            return TAPPING_TERM + 100;
        default:
            return TAPPING_TERM;
    }
}
#endif

#ifdef RGB_MATRIX_ENABLE
void suspend_power_down_keymap(void) { rgb_matrix_set_suspend_state(true); }

void suspend_wakeup_init_keymap(void) { rgb_matrix_set_suspend_state(false); }

void check_default_layer(uint8_t mode, uint8_t type, uint8_t led_min, uint8_t led_max) {
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            rgb_matrix_layer_helper(DEFAULT_LAYER_1_HSV, mode, rgb_matrix_config.speed, type, led_min, led_max);
            break;
        case _COLEMAK_DH:
            rgb_matrix_layer_helper(DEFAULT_LAYER_2_HSV, mode, rgb_matrix_config.speed, type, led_min, led_max);
            break;
        case _COLEMAK:
            rgb_matrix_layer_helper(DEFAULT_LAYER_3_HSV, mode, rgb_matrix_config.speed, type, led_min, led_max);
            break;
        case _DVORAK:
            rgb_matrix_layer_helper(DEFAULT_LAYER_4_HSV, mode, rgb_matrix_config.speed, type, led_min, led_max);
            break;
    }
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (userspace_config.rgb_layer_change) {
        switch (get_highest_layer(layer_state)) {
            case _GAMEPAD:
                rgb_matrix_layer_helper(HSV_ORANGE, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW, led_min, led_max);
                break;
            case _DIABLO:
                rgb_matrix_layer_helper(HSV_RED, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW, led_min, led_max);
                break;
            case _RAISE:
                rgb_matrix_layer_helper(HSV_YELLOW, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW, led_min, led_max);
                break;
            case _LOWER:
                rgb_matrix_layer_helper(HSV_GREEN, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW, led_min, led_max);
                break;
            case _ADJUST:
                rgb_matrix_layer_helper(HSV_RED, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW, led_min, led_max);
                break;
            default:
                {
                    check_default_layer(0, LED_FLAG_UNDERGLOW, led_min, led_max);
                    break;
                }
        }
        check_default_layer(0, LED_FLAG_MODIFIER, led_min, led_max);
    }
}
#endif
