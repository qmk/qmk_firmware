/* Copyright 2020 imchipwood
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
#include <print.h>
#include <imchipwood.h>

#define _BASE 0
#define _SUB 1
#define _DBG 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
          BASE LAYER
     /-----------------------------------------------------`
     |             |    7    |    8    |    9    |  Bkspc  |
     |             |---------|---------|---------|---------|
     |             |    4    |    5    |    6    |    +    |
     |             |---------|---------|---------|---------|
     |             |    1    |    2    |    3    |    *    |
     |-------------|---------|---------|---------|---------|
     | Play/Pause  | TT(SUB) |    0    |    .    |  Enter  |
     \-----------------------------------------------------'
    */
    [_BASE] = LAYOUT(
                   KC_P7,      KC_P8,    KC_P9,     KC_BSPC,
                   KC_P4,      KC_P5,    KC_P6,     KC_KP_PLUS,
                   KC_P1,      KC_P2,    KC_P3,     KC_KP_ASTERISK,
        KC_MPLY,   TT(_SUB),   KC_P0,    KC_PDOT,   KC_KP_ENTER
    ),
    /*
          SUB LAYER
     /-----------------------------------------------------`
     |             |   F7    |   F8    |   F9    | Del/NLK |
     |             |---------|---------|---------|---------|
     |             |   F4    |   F5    |   F6    |    -    |
     |             |---------|---------|---------|---------|
     |             |   F1    |   F2    |   F3    |    /    |
     |-------------|---------|---------|---------|---------|
     |  MO(_DBG)   |         |  LSFT   |  LCTL   |    =    |
     \-----------------------------------------------------'
    */
    [_SUB] = LAYOUT(
                   TD(ALT_F7),       KC_F8,       KC_F9,           TD(DEL_NLCK),
                        KC_F4,   TD(CTL_F5),      KC_F6,           KC_KP_MINUS,
                        KC_F1,       KC_F2,       KC_F3,           KC_KP_SLASH,
        MO(_DBG),     _______,   OSM(MOD_LSFT),   OSM(MOD_LCTL),   KC_KP_EQUAL
    ),
    /*
          DEBUG LAYER
     /-----------------------------------------------------`
     |             |         |         |         |  Reset  |
     |             |---------|---------|---------|---------|
     |             |         |         |         |         |
     |             |---------|---------|---------|---------|
     |             |         |         |         |         |
     |-------------|---------|---------|---------|---------|
     |             |         |         |         |  DEBUG  |
     \-----------------------------------------------------'
    */
    [_DBG] = LAYOUT(
             _______, _______, _______, RESET,
             _______, _______, _______, _______,
             _______, _______, _______, _______,
    _______, _______, _______, _______, DEBUG
    ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    dprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
    return true;
}

/*
void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    debug_matrix = true;
    debug_keyboard = true;
    debug_mouse = true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef CONSOLE_ENABLE
    uint8_t layer_state = biton32(state);
    dprintf("layer_state:   %u\n", layer_state);
#endif
    return state;
}
*/

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            case _BASE:
                // main layer - volume up/down
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;

            case _SUB:
                // sub layer - next/previous track
                if (clockwise) {
                    tap_code(KC_MNXT);
                } else {
                    tap_code(KC_MPRV);
                }
                break;

            case _DBG:
                // debug layer - mouse wheel up/down
                if (clockwise) {
                    tap_code(KC_WH_D);
                } else {
                    tap_code(KC_WH_U);
                }
                break;

            default:
                // default - volume up/down
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
        }
    }
}
