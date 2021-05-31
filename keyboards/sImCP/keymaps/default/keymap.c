/* Copyright 2021 dsanchezseco
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
};

enum {
    DOB_PUSH,
    FUN1 = LCTL(KC_A),
    FUN2 = LCTL(KC_O),
    FUN3 = LCTL(KC_U),
    FUN4 = LCTL(KC_I),
    SEL1 = LCTL(KC_D),
    SEL2 = LCTL(KC_H),
    SEL3 = LCTL(KC_T),
    SEL4 = LCTL(KC_N),
    SEL5 = LCTL(KC_SCLN),
    N1 = RCTL(KC_1),
    N2 = RCTL(KC_2),
    N3 = RCTL(KC_3),
    N4 = RCTL(KC_4),
    N5 = RCTL(KC_5),
    N6 = RCTL(KC_6),
    N7 = RCTL(KC_7),
    N8 = RCTL(KC_8),
    N9 = RCTL(KC_9),
    N0 = RCTL(KC_0),
    ENT = RCTL(KC_LBRC),
    CRL = RCTL(KC_RBRC),
    COM1P = LCTL(KC_Q),
    COM2P = LCTL(KC_J),
    UP = LCTL(KC_K),
    DOWN = LCTL(KC_X),
    DOB_UP = LCTL(KC_M),
    DOB_DOWN = LCTL(KC_V),
    DOB_LEFT = RCTL(KC_M),
    DOB_RIGHT = RCTL(KC_V),
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [DOB_PUSH] = ACTION_TAP_DANCE_DOUBLE(KC_NO, RCTL(KC_W)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        FUN1,   FUN2,       FUN3,       FUN4,       SEL1,
        N1,     N2,         N3,         COM1P,      SEL2,
        N4,     N5,         N6,         COM2P,      SEL3,
        N7,     N8,         N9,         UP,         SEL4,
        CRL,    N0,         ENT,        DOWN,       SEL5,
        DOB_UP, DOB_LEFT,   DOB_DOWN,   DOB_RIGHT,  TD(DOB_PUSH)
    ),
};

void led_keypress_update(pin_t led_pin, uint16_t keycode, keyrecord_t *record) {
    // When a key is pressed turn on the LED, when released turn it off
    writePin(led_pin, !record->event.pressed);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Update LED state
    led_keypress_update(LED, keycode, record);
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Encoder on the LEFT */
        if (clockwise) {
            tap_code16(RCTL(KC_A));
        } else {
            tap_code16(RCTL(KC_O));
        }
    } else if (index == 1) { /* Encoder on the RIGHT */
        if (clockwise) {
            tap_code16(RCTL(KC_U));
        } else {
            tap_code16(RCTL(KC_I));
        }
    } else if (index == 2) { /* Encoder on the RIGHT */
        if (clockwise) {
            tap_code16(RCTL(KC_H));
        } else {
            tap_code16(RCTL(KC_D));
        }
    }
}

