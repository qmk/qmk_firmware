/* Copyright 2020 grid
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

// #define LED_DEBUG

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};


// USB keymap for user
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_650(
        QK_GESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_GRV,  KC_BSPC,  KC_BSPC,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS, KC_PGUP,  KC_DEL,     
        KC_CAPS,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_BSLS, KC_ENT,  KC_PGDN,
        KC_LSFT,     KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,   MO(_FN),
        KC_LCTL,     KC_LGUI, KC_LALT,                   KC_SPACE,                           KC_RALT, KC_RGUI, KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT,
        KC_F1,       KC_F2,   KC_F3,   KC_F4
    ),
    [_FN] = LAYOUT_650(
        KC_GRV,     KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_F13,  KC_DEL,   KC_DEL,
        KC_TRNS,    KC_BTN1,  KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_HOME,  KC_BSPC,
        KC_TRNS,    KC_MS_L,  KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_END,
        KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_VOLU, KC_INS,
        KC_TRNS,    KC_TRNS,  KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS,  KC_MPRV, KC_VOLD, KC_MNXT,
        KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS    
    )
};





/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
