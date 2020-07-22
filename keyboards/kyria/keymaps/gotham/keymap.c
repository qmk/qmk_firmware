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

#include QMK_KEYBOARD_H
#include "gotham.h"

enum custom_keycodes {
    ENC_MODE_L = NEW_SAFE_RANGE,
    ENC_MODE_R,
    TMB_MODE,
};

enum encoder_names {
    ENCODER_LEFT = 0,
    ENCODER_RIGHT,
};

/*
 * The `LAYOUT_kyria_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

// clang-format off
#define LAYOUT_kyria_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
      KC_ESC,   K01,  K02,  K03,  K04,  K05,                                           K06,  K07,  K08,  K09,  K0A,  KC_BSLS, \
      KC_LSFT,  K11,  K12,  K13,  K14,  K15,                                           K16,  K17,  K18,  K19,  K1A,  RSFT_T(KC_QUOT), \
      KC_LCTL,  K21,  K22,  K23,  K24,  K25,  KC_CCCV, TG_GAME,  TMB_MODE, TMB_MODE, K26,  K27,  K28,  K29,  K2A,  RCTL_T(KC_MINS), \
                ENC_MODE_L, KC_LALT, SP_LOWR, TB_RAIS, KC_LGUI,  KC_EQL, EN_LOWR, BK_RAIS, KC_DEL, ENC_MODE_R \
    )
/* Re-pass though to allow templates to be used */
#define LAYOUT_kyria_base_wrapper(...)       LAYOUT_kyria_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_kyria_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_COLEMAK] = LAYOUT_kyria_base_wrapper(
        _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
        _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
    ),

    [_DVORAK] = LAYOUT_kyria_base_wrapper(
        _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
        _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
        _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
    ),

    [_WORKMAN] = LAYOUT_kyria_base_wrapper(
        _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
        _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
        _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
    ),

    [_NORMAN] = LAYOUT_kyria_base_wrapper(
        _________________NORMAN_L1_________________, _________________NORMAN_R1_________________,
        _________________NORMAN_L2_________________, _________________NORMAN_R2_________________,
        _________________NORMAN_L3_________________, _________________NORMAN_R3_________________
    ),

    [_GAME] = LAYOUT_wrapper(
      LT(_GAMENUM, KC_T), __________________GAME_L1__________________,                                       _________________QWERTY_R1_________________, KC_BSLS,
      LT(_GAMENUM, KC_G), __________________GAME_L2__________________,                                       _________________QWERTY_R2_________________, KC_RSFT,
      LT(_GAMENUM, KC_B), __________________GAME_L3__________________, KC_NO, _______,  TMB_MODE, KC_NO, _________________QWERTY_R3_________________, KC_RCTL,
                      ENC_MODE_L, KC_LALT, KC_SPC, LT(_GAMENUM, KC_TAB), MO(_GAMENUM),  KC_EQL, KC_ENT, KC_BSPC, KC_DEL, ENC_MODE_R
    ),

    [_GAMENUM] = LAYOUT_wrapper(
      _______,  KC_NO,  KC_1,   KC_2,   KC_3,   KC_NO,                                      KC_NO,  KC_F1,  KC_F2,  KC_F3,  KC_F10, KC_NO,
      _______,  KC_0,   KC_4,   KC_5,   KC_6,   KC_NO,                                      KC_NO,  KC_F4,  KC_F5,  KC_F6,  KC_F11, _______,
      _______,  KC_NO,  KC_7,   KC_8,   KC_9,   KC_NO,  KC_NO,  KC_NO,      KC_NO,  KC_NO,  KC_NO,  KC_F7,  KC_F8,  KC_F9,  KC_F12, _______,
                          _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),

    [_LOWER] = LAYOUT_kyria_base_wrapper(
        _________________LOWER_L1__________________, _________________LOWER_R1__________________,
        _________________LOWER_L2__________________, _________________LOWER_R2__________________,
        _________________LOWER_L3__________________, _________________LOWER_R3__________________
    ),

    [_RAISE] = LAYOUT_kyria_base_wrapper(
        _________________RAISE_L1__________________, _________________RAISE_R1__________________,
        _________________RAISE_L2__________________, _________________RAISE_R2__________________,
        _________________RAISE_L3__________________, _________________RAISE_R3__________________
    ),

    [_ADJUST] = LAYOUT_kyria_base_wrapper(
        _________________ADJUST_L1_________________, _________________ADJUST_R1_________________,
        _________________ADJUST_L2_________________, _________________ADJUST_R2_________________,
        _________________ADJUST_L3_________________, _________________ADJUST_R3_________________
    ),
};
// clang-format on

layer_state_t layer_state_set_keymap(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }

#ifdef THUMBSTICK_ENABLE
bool process_record_keymap_thumbstick(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TMB_MODE:
            if (record->event.pressed) {
                thumbstick_mode_cycle_forward();
            }
    }
    return true;
}
#endif

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_keymap(oled_rotation_t rotation) { return OLED_ROTATION_180; }
#endif

#ifdef ENCODER_ENABLE
void encoder_init_keymap(void) {
    encoder_mode_hand_set(ENCODER_HAND_LEFT, 0, ENC_MODE_VOLUME);
    encoder_mode_hand_set(ENCODER_HAND_RIGHT, 0, ENC_MODE_LEFT_RIGHT);
}

bool process_record_keymap_encoder(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case ENC_MODE_L:
                encoder_mode_hand_next(ENCODER_HAND_LEFT, 0);
                return false;
                break;
            case ENC_MODE_R:
                encoder_mode_hand_previous(ENCODER_HAND_RIGHT, 0);
                return false;
                break;
        }
    }
    return true;
}
#endif
