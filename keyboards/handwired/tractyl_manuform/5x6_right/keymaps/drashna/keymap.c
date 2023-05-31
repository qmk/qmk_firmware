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

// clang-format off
#define LAYOUT_5x6_right_wrapper(...) LAYOUT_5x6_right(__VA_ARGS__)
#define LAYOUT_5x6_right_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_5x6_right_wrapper( \
     KC_ESC,  ________________NUMBER_LEFT________________,            ________________NUMBER_RIGHT_______________, UC_CLUE, \
     SH_TT,   K01,    K02,      K03,     K04,     K05,                K06,     K07,     K08,     K09,     K0A,     SH_TT, \
     LALT_T(KC_TAB), K11, K12,  K13,     K14,     K15,                K16,     K17,     K18,     K19,     K1A,     RALT_T(K1B), \
     OS_LSFT, CTL_T(K21), K22,  K23,     K24,     K25,                K26,     K27,     K28,     K29, RCTL_T(K2A), OS_RSFT, \
                       OS_LALT, OS_LGUI,                                                OS_RGUI, OS_RALT, \
                                KC_MUTE, KC_GRV,                                        KC_BTN3,  \
                                         KC_SPC,  UC_IRNY,                     KC_ENT,  \
                                         BK_LWER, TT(_MOUSE),      TT(_MOUSE), DL_RAIS  \
  )
#define LAYOUT_base_wrapper(...)       LAYOUT_5x6_right_base(__VA_ARGS__)

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

    [_GAMEPAD] = LAYOUT_5x6_right(
        KC_ESC,  KC_NO,   KC_1,    KC_2,    KC_3,    KC_4,                           _______, _______, _______, _______, _______, _______,
        KC_F1,   KC_K,    KC_Q,    KC_W,    KC_E,    KC_R,                           _______, _______, _______, _______, _______, _______,
        KC_TAB,  KC_G,    KC_A,    KC_S,    KC_D,    KC_F,                           _______, _______, _______, _______, _______, _______,
        KC_LCTL, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_H,                           _______, _______, _______, _______, _______, _______,
                          KC_I,    KC_T,                                                               TG_GAME, KC_NO,
                                            KC_V,    KC_O,                                    _______,
                                                     KC_SPC,  KC_P,                  _______,
                                                     KC_H,    KC_LGUI,      _______, _______
    ),
    [_DIABLO] = LAYOUT_5x6_right(
        KC_ESC,  KC_V,    KC_D,    KC_LALT, KC_NO,   KC_NO,                          KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,
        KC_TAB,  KC_S,    KC_I,    KC_F,    KC_M,    KC_T,                           _______, _______, _______, _______, _______, _______,
        KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,    KC_G,                           _______, _______, _______, _______, _______, _______,
        KC_LCTL, KC_D3_1, KC_D3_2, KC_D3_3, KC_D3_4, KC_Z,                           _______, _______, _______, _______, _______, _______,
                          KC_F,    KC_L,                                                               KC_NO,   TG_DBLO,
                                    KC_DIABLO_CLEAR, KC_F,                                    _______,
                                               SFT_T(KC_SPC), KC_J,                  _______,
                                               ALT_T(KC_Q),   KC_LGUI,      _______, _______
    ),
    [_DIABLOII] = LAYOUT_5x6_right(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_GRV,                         _______, _______, _______, _______, _______, _______,
        KC_TAB,  KC_A,    KC_T,    KC_Q,    KC_I,    KC_M,                           _______, _______, _______, _______, _______, _______,
        KC_S,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                          _______, _______, _______, _______, _______, _______,
        KC_LCTL, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                         _______, _______, _______, _______, _______, _______,
                          KC_F,    KC_L,                                                               KC_NO,   TG(_DIABLOII),
                                   _______, KC_G,                                             _______,
                                               KC_LSFT, _______,                     _______,
                                               KC_LCTL, KC_V,               _______, _______
    ),
    [_MOUSE] = LAYOUT_5x6_right(
        _______, _______, _______, _______, _______, _______,                        _______, DPI_RMOD,DPI_MOD, S_D_RMOD,S_D_MOD, PD_JIGGLER,
        _______, _______, _______, _______, _______, _______,                        KC_WH_U, _______, _______, _______, _______, DRGSCRL,
        _______, _______, _______, _______, _______, _______,                        KC_WH_D, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN6, SNIPING,
        _______, _______, _______, _______, _______, _______,                        KC_BTN7, KC_BTN4, KC_BTN5, KC_BTN8, _______, _______,
                          _______, _______,                                                            _______, _______,
                                            _______, _______,                                 KC_BTN3,
                                                     _______, _______,               _______,
                                                     _______, _______,      _______, _______
    ),
    [_LOWER] = LAYOUT_5x6_right_wrapper(
        KC_F12,  _________________FUNC_LEFT_________________,                        _________________FUNC_RIGHT________________, KC_F11,
        _______, _________________LOWER_L1__________________,                        _________________LOWER_R1__________________, _______,
        _______, _________________LOWER_L2__________________,                        _________________LOWER_R2__________________, KC_PIPE,
        _______, _________________LOWER_L3__________________,                        _________________LOWER_R3__________________, _______,
                          _______, _______,                                                            _______, _______,
                                            _______, _______,                                 _______,
                                                     _______, _______,               _______,
                                                     _______, _______,      _______, _______
    ),
    [_RAISE] = LAYOUT_5x6_right_wrapper(
        KC_F12,  _________________FUNC_LEFT_________________,                        _________________FUNC_RIGHT________________, KC_F11,
        KC_GRV,  _________________RAISE_L1__________________,                        _________________RAISE_R1__________________, _______,
        _______, _________________RAISE_L2__________________,                        _________________RAISE_R2__________________, KC_BSLS,
        _______, _________________RAISE_L3__________________,                        _________________RAISE_R3__________________, _______,
                          _______, _______,                                                            _______, _______,
                                            OL_LOCK, _______,                                 _______,
                                                     _______, _______,               _______,
                                                     _______, _______,      _______, _______
    ),
    [_ADJUST] = LAYOUT_5x6_right_wrapper(
        QK_MAKE, KC_WIDE,KC_AUSSIE,KC_SCRIPT,KC_ZALGO,KC_NOMODE,                 KC_NOMODE,KC_BLOCKS,KC_REGIONAL,_______,_______, QK_BOOT,
        VRSN,    _________________ADJUST_L1_________________,                        _________________ADJUST_R1_________________, EE_CLR,
        KEYLOCK, _________________ADJUST_L2_________________,                        _________________ADJUST_R2_________________, TG_MODS,
        UC_NEXT, _________________ADJUST_L3_________________,                        _________________ADJUST_R3_________________, KC_MPLY,
                   TG(_DIABLOII), AUTO_CTN,                                                            TG_GAME, TG_DBLO,
                                            _______, QK_RBT,                                  KC_NUKE,
                                                     HF_TOGG, _______,               _______,
                                                     _______, _______,      KC_NUKE, _______
    ),
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_DEFAULT_LAYER_1] = { ENCODER_CCW_CW( KC_VOLU, KC_VOLD ), ENCODER_CCW_CW( KC_WH_U, KC_WH_D ) },
    [_DEFAULT_LAYER_2] = { ENCODER_CCW_CW( _______, _______ ), ENCODER_CCW_CW( _______, _______ ) },
    [_DEFAULT_LAYER_3] = { ENCODER_CCW_CW( _______, _______ ), ENCODER_CCW_CW( _______, _______ ) },
    [_DEFAULT_LAYER_4] = { ENCODER_CCW_CW( _______, _______ ), ENCODER_CCW_CW( _______, _______ ) },
    [_GAMEPAD]         = { ENCODER_CCW_CW( _______, _______ ), ENCODER_CCW_CW( _______, _______ ) },
    [_DIABLO]          = { ENCODER_CCW_CW( _______, _______ ), ENCODER_CCW_CW( _______, _______ ) },
    [_MOUSE]           = { ENCODER_CCW_CW( _______, _______ ), ENCODER_CCW_CW( _______, _______ ) },
    [_MEDIA]           = { ENCODER_CCW_CW( _______, _______ ), ENCODER_CCW_CW( _______, _______ ) },
    [_RAISE]           = { ENCODER_CCW_CW( OL_BINC, OL_BDEC ), ENCODER_CCW_CW( KC_PGDN, KC_PGUP ) },
    [_LOWER]           = { ENCODER_CCW_CW( RGB_MOD, RGB_RMOD), ENCODER_CCW_CW( RGB_HUI, RGB_HUD ) },
    [_ADJUST]          = { ENCODER_CCW_CW( CK_UP,   CK_DOWN ), ENCODER_CCW_CW( _______, _______ ) },
};
// clang-format on
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_keymap(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

void render_oled_title(bool side) {
    oled_write_P(side ? PSTR("   Tractyl   ") : PSTR("   Manuform  "), true);
}
#endif
