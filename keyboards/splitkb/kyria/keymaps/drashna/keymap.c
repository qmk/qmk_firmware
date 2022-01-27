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

/*
 * The `LAYOUT_kyria_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

// clang-format off
#define LAYOUT_wrapper(...)            LAYOUT(__VA_ARGS__)
#define LAYOUT_kyria_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
      KC_ESC,  K01,     K02,     K03,     K04,     K05,                                             K06,     K07,     K08,     K09,     K0A,     KC_MINS, \
   LALT_T(KC_TAB), K11, K12,     K13,     K14,     K15,                                             K16,     K17,     K18,     K19,     K1A, RALT_T(K1B), \
      OS_LSFT, CTL_T(K21), K22,  K23,     K24,     K25,  TG_GAME, MEH(KC_MINS),   TG_DBLO, KC_CAPS, K26,     K27,     K28,     K29, RCTL_T(K2A), OS_RSFT, \
                                 KC_MUTE, OS_LALT, KC_GRV,  KC_SPC,  BK_LWER,     DL_RAIS, KC_ENT,  OS_RGUI, UC(0x03A8), UC(0x2E2E) \
    )
/* Re-pass though to allow templates to be used */
#define LAYOUT_base_wrapper(...)       LAYOUT_kyria_base(__VA_ARGS__)

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

    [_GAMEPAD] = LAYOUT_wrapper(
        KC_ESC,  KC_K,    KC_Q,    KC_W,    KC_E,    KC_R,                                          _______, _______, _______, _______, _______, _______,
        KC_TAB,  KC_G,    KC_A,    KC_S,    KC_D,    KC_F,                                          _______, _______, _______, _______, _______, _______,
        KC_LCTL, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    _______, _______,   _______, LALT(KC_PSCR), _______, _______, _______, _______, _______, _______,
                                  _______, MAGIC_TOGGLE_NKRO, KC_V,     KC_SPC,  KC_H,   _______, _______, _______, _______, _______
    ),

    [_DIABLO] = LAYOUT_wrapper(
        KC_ESC,  KC_S,    KC_I,    KC_F,    KC_M,    KC_T,                                          KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,
        KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_G,                                          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LCTL, KC_D3_1, KC_D3_2, KC_D3_3, KC_D3_4, KC_Z,    KC_J,    KC_L,        TG_DBLO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                           KC_DIABLO_CLEAR, KC_J,    KC_NO, SFT_T(KC_SPACE), ALT_T(KC_Q),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),
    [_LOWER] = LAYOUT_wrapper(
        KC_F12,  _________________LOWER_L1__________________,                                       _________________LOWER_R1__________________, KC_F11,
        _______, _________________LOWER_L2__________________,                                       _________________LOWER_R2__________________, KC_PIPE,
        _______, _________________LOWER_L3__________________, _______, _______,   _______, _______, _________________LOWER_R3__________________, _______,
                                   _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______
    ),
    [_RAISE] = LAYOUT_wrapper(
        KC_F12,  _________________RAISE_L1__________________,                                       _________________RAISE_R1__________________, KC_F11,
        _______, _________________RAISE_L2__________________,                                       _________________RAISE_R2__________________, KC_BSLS,
        _______, _________________RAISE_L3__________________, _______, _______,   _______, _______, _________________RAISE_R3__________________, _______,
                                   _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT_wrapper(
        KC_MAKE, _________________ADJUST_L1_________________,                                       _________________ADJUST_R1_________________, KC_RESET,
        VRSN,    _________________ADJUST_L2_________________,                                       _________________ADJUST_R2_________________, EEP_RST,
        UC_MOD,  _________________ADJUST_L3_________________, HPT_TOG, HPT_FBK,   MG_NKRO, UC_MOD,  _________________ADJUST_R3_________________, TG_MODS,
                                   REBOOT,  _______, KEYLOCK, KC_NUKE, _______,   _______, _______, _______, _______, AUTO_CTN
    ),
//     [_LAYERINDEX] = LAYOUT_wrapper(
//       _______, _______, _______, _______, _______, _______,                                       _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                       _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______
//     ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_DEFAULT_LAYER_1] = { { KC_DOWN, KC_UP   }, { KC_VOLD, KC_VOLU } },
    [_DEFAULT_LAYER_2] = { { _______, _______ }, { _______, _______ } },
    [_DEFAULT_LAYER_3] = { { _______, _______ }, { _______, _______ } },
    [_DEFAULT_LAYER_4] = { { _______, _______ }, { _______, _______ } },
    [_GAMEPAD]         = { { _______, _______ }, { _______, _______ } },
    [_DIABLO]          = { { _______, _______ }, { _______, _______ } },
    [_MOUSE]           = { { _______, _______ }, { KC_WH_D, KC_WH_U } },
    [_MEDIA]           = { { _______, _______ }, { _______, _______ } },
    [_RAISE]           = { { _______, _______ }, { KC_PGDN, KC_PGUP } },
    [_LOWER]           = { { RGB_MOD, RGB_RMOD}, { RGB_HUD, RGB_HUI } },
    [_ADJUST]          = { { CK_DOWN, CK_UP   }, { _______, _______ } },
};
#endif
// clang-format on

#ifdef OLED_ENABLE
oled_rotation_t oled_init_keymap(oled_rotation_t rotation) { return OLED_ROTATION_180; }
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}
#endif

#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM shift_layers[]   = RGBLIGHT_LAYER_SEGMENTS({8, 1, 120, 255, 255}, {18, 1, 120, 255, 255});
const rgblight_segment_t PROGMEM control_layers[] = RGBLIGHT_LAYER_SEGMENTS({6, 1, 0, 255, 255}, {16, 1, 0, 255, 255});
const rgblight_segment_t PROGMEM alt_layers[]     = RGBLIGHT_LAYER_SEGMENTS({2, 1, 240, 255, 255}, {17, 1, 250, 255, 255});
const rgblight_segment_t PROGMEM gui_layers[]     = RGBLIGHT_LAYER_SEGMENTS({7, 1, 51, 255, 255}, {12, 1, 51, 255, 255});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(shift_layers, control_layers, alt_layers, gui_layers);

void keyboard_post_init_keymap(void) { rgblight_layers = my_rgb_layers; }

void matrix_scan_keymap(void) {
    uint8_t mods = mod_config(get_mods() | get_oneshot_mods());
    rgblight_set_layer_state(0, mods & MOD_MASK_SHIFT);
    rgblight_set_layer_state(1, mods & MOD_MASK_CTRL);
    rgblight_set_layer_state(2, mods & MOD_MASK_ALT);
    rgblight_set_layer_state(3, mods & MOD_MASK_GUI);
}
#endif
