/* Copyright 2021 Omar Afzal
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
#include "features/custom_shift_keys.h"

#define FN_ESC LT(_FUNC, KC_ESC)

enum gentleman_layers {
    _QWERTY,
    _WORKMAN,
    _FUNC,
};

enum gentleman_keycodes {
    QWERTY = SAFE_RANGE,
    WORKMAN,
    FUNC,
};

const custom_shift_key_t custom_shift_keys[] = {{KC_ESC, KC_TILD}};

uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_65_ansi_rwkl_split_bs(
		KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,  KC_TRNS,
		KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,           KC_BSLS, KC_DEL,
		FN_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,            KC_PGUP,
		KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,           KC_UP,   KC_PGDN,
		KC_LCTL,  KC_LGUI, KC_LALT,                            KC_SPC,                            KC_RALT,  KC_RCTL,          KC_LEFT, KC_DOWN,  KC_RGHT
    ),

	[_WORKMAN] = LAYOUT_65_ansi_rwkl_split_bs(
		KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,  KC_TRNS,
		KC_TAB,   KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, KC_LBRC, KC_RBRC,          KC_BSLS,  KC_DEL,
		FN_ESC,   KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    KC_QUOT,          KC_ENT,            KC_PGUP,
		KC_LSFT,           KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,            KC_UP,  KC_PGDN,
		KC_LCTL,  KC_LGUI, KC_LALT,                            KC_SPC,                            KC_RALT,  KC_RCTL,          KC_LEFT, KC_DOWN,  KC_RGHT
    ),

    [_FUNC] = LAYOUT_65_ansi_rwkl_split_bs(
        KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, QK_BOOT,
        KC_TRNS,  KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP,   AG_NORM, AG_SWAP, QWERTY,  WORKMAN,          KC_TRNS, KC_INS,
        KC_TRNS,  KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME, KC_END,           KC_TRNS,          KC_HOME,
        KC_TRNS,           KC_WH_L, KC_BTN3, KC_WH_R, KC_TRNS, RGB_TOG, RGB_MOD, RGB_VAI, RGB_VAD, RGB_SAI, RGB_SAD, KC_TRNS,          RGB_HUI, KC_END,
        KC_TRNS,  KC_TRNS, KC_TRNS,                            KC_MPLY,                            KC_TRNS, KC_TRNS,          KC_MPRV, RGB_HUD, KC_MNXT
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _FUNC:
                // Vertical Scroll
                clockwise ? tap_code(KC_WH_D) : tap_code(KC_WH_U);
                return false;
                break;
            default:
                // Horizontal Scroll
                if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    clockwise ? tap_code(KC_WH_D) : tap_code(KC_WH_U);
                    return false;
                }
                // Volume
                clockwise ? tap_code(KC_AUDIO_VOL_UP) : tap_code(KC_AUDIO_VOL_DOWN);
                break;
        }
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case WORKMAN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WORKMAN);
            }
            return false;
    }

    return true;
}
