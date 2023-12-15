/* Copyright 2023 GSKY <gskyGit@gsky.com.tw>
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
enum my_keycodes {
    RGB_R = QK_USER,
    RGB_G,
    RGB_B,
    RGB_W,
    SW_cy,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case RGB_R:
            if (record->event.pressed) {
                rgb_matrix_sethsv(0, 255, 255);
                rgb_matrix_mode(1);
            }
            return false; /* Skip all further processing of this key */

        case RGB_G:
            if (record->event.pressed) {
                rgb_matrix_sethsv(85, 255, 255);
                rgb_matrix_mode(1);
            }
            return false; /* Skip all further processing of this key */

        case RGB_B:
            if (record->event.pressed) {
                rgb_matrix_sethsv(170, 255, 255);
                rgb_matrix_mode(1);
            }
            return false; /* Skip all further processing of this key */

        case RGB_W:
            if (record->event.pressed) {
                rgb_matrix_sethsv(0, 0, 255);
                rgb_matrix_mode(1);
            }
            return false; /* Skip all further processing of this key */

        case SW_cy:
            rgb_matrix_sethsv(0, 255, 255);
            rgb_matrix_mode(13);
            return false; /* Skip all further processing of this key */

        
        default:
            return true; /* Process all other keycodes normally */
    }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[0] = LAYOUT(
            QK_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,         KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,
            KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,         KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
            KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,         KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGDN,
            KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,       KC_SLSH,  KC_RSFT,            KC_UP,    KC_END,
            KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,                                 KC_RALT,      MO(1),              KC_LEFT,  KC_DOWN,  KC_RGHT),
[1] = LAYOUT(
            KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,        KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_TRNS,
            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  RGB_TOG,  RGB_MOD,  RGB_RMOD, KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
            KC_LSFT,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_RSFT,            RGB_VAI,  KC_TRNS,
            KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,                                MO(2),        KC_TRNS,            RGB_SPD,  RGB_VAD,  RGB_SPI),
[2] = LAYOUT(
            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
            QK_BOOT,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
            KC_TRNS,  RGB_R,    RGB_G,    RGB_B,    RGB_W,    SW_cy,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
            KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,                                KC_TRNS,      KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS),
};
