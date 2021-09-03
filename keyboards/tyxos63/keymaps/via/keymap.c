/* Copyright 2021 marby3
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

// Defines the keycodes used by our macros in process_record_user
#define RAISE   LT(_RAISE,KC_HENK) //Tap to Henkan(/w AHK Assistance)
#define LOWER   LT(_LOWER,KC_MHEN) //Tap to Muhenkan(/w AHK Assistance)
//#define RAISE MO(_RAISE) //Not Defined Tap Code
//#define LOWER MO(_LOWER) //Not Defined Tap Code
#define ADJUST  MO(_ADJUST) //Holding RAISE and LOWER
#define UNDO    LCTL(KC_Z)
#define REDO    LCTL(KC_Y)
#define CUT     LCTL(KC_X)
#define COPY    LCTL(KC_C)
#define PASTE   LCTL(KC_V)
#define SAVE    LCTL(KC_S)
#define KC_XXXX KC_NO

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _RAISE,
    _LOWER,
    _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, SAVE,    KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, KC_MINS, KC_EQL,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,         KC_ENT,      KC_LBRC, KC_RBRC,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_SLSH,    KC_RSFT,    KC_RCTL,    KC_SCLN, KC_QUOT,
        RAISE,   KC_LGUI, KC_LALT,                        KC_SPC,                        KC_RALT, KC_RGUI, LOWER,   KC_COMM, KC_DOT
    ),
    [_RAISE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,  _______, _______,
        _______, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX,
        _______, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX,      _______,     CUT, KC_XXXX,
        _______, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX,    KC_UP,      _______,    COPY,    PASTE,
        _______, _______, _______,                        _______,                       KC_LEFT, KC_DOWN, KC_RGHT, UNDO,    REDO
    ),
    [_LOWER] = LAYOUT(
        KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, _______, _______,
        KC_PSCR, KC_PGUP, KC_UP,   KC_PGDN, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX,      _______,     KC_XXXX, KC_XXXX,
        _______, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX,    _______,    _______,    KC_XXXX, KC_XXXX,
        ADJUST,  _______, _______,                        _______,                       _______, _______, _______, KC_XXXX, KC_XXXX
    ),
    [_ADJUST] = LAYOUT(
        KC_XXXX, RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, KC_XXXX, _______, _______,
        _______, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, RGB_MOD, RGB_RMOD,
        _______, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX,      _______,     RGB_HUI, RGB_HUD,
        _______, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX, KC_XXXX,    _______,    _______,    RGB_SAI, RGB_SAD,
        _______, _______, _______,                        _______,                       _______, _______, _______, RGB_VAI, RGB_VAD
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // Left encoder
        if (clockwise) {
            tap_code16(C(KC_Y));
        } else {
            tap_code16(C(KC_Z));
        }
    }
    else if (index == 1) { // Right encoder
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
