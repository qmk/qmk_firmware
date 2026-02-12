/* Copyright 2025 BlackMullerLLC
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
#include "raw_hid.h"

#define RAW_HID_MSG_LEN 32

enum custom_keycodes
{
    LAYER_SYNC = SAFE_RANGE,
};

enum eDriverCMD
{
    defaultLayer = 0x1,
    layer1 = 0x2
};


bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case LAYER_SYNC:

            uint8_t command[RAW_HID_MSG_LEN] = {0};
            if (record->event.pressed) {
                layer_move(1);
                command[0] = layer1;
            } else {
                layer_move(0);
                command[0] = defaultLayer;
            }
            raw_hid_send(command, RAW_HID_MSG_LEN);
            return false; // stop further handling
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┐
     * │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │
     * └───┘   └───┴───┴───┴───┘ └───┴───┘
     * ┌───┬───┬───┬───┬───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘
     * │ Tab │ Q │ W │ E │ R │ T │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐
     * │ Caps │ A │ S │ D │ F │ G │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐
     * │ Shift  │ Z │ X │ C │ V │ B │
     * ├────┬───┴┬──┴─┬─┴───┴───┴──┬┴──────────┐
     * │Ctrl│GUI │Alt │   LAYER    │   Space   │
     * └────┴────┴────┴────────────┴───────────┘
     */
    [0] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,       KC_F5,   KC_F6,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,
        KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,        KC_T,
        KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,        KC_G,
                 KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,        KC_B,
        KC_LCTL, KC_LGUI,          KC_LALT,          LAYER_SYNC,  KC_SPC
    )
    ,
    [1] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,       KC_F5,   KC_F6,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,
        KC_TAB,           KC_Q,    KC_W,    S(KC_9), S(KC_0),     KC_T,
        KC_CAPS,          KC_A,    KC_S,    KC_LBRC, KC_RBRC,     KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
        KC_LCTL, KC_LGUI,          KC_LALT,          LAYER_SYNC,  KC_SPC
    )
};
