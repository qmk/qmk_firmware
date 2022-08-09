/* Copyright 2021 AndyChiu
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


keyevent_t encoder1_ccw = {
    .key = (keypos_t){.row = 1, .col = 7},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .key = (keypos_t){.row = 0, .col = 7},
    .pressed = false
};

keyevent_t encoder2_ccw = {
    .key = (keypos_t){.row = 2, .col = 7},
    .pressed = false
};

keyevent_t encoder2_cw = {
    .key = (keypos_t){.row = 3, .col = 7},
    .pressed = false
};

void matrix_scan_user(void) {
    if (IS_PRESSED(encoder1_ccw)) {
        encoder1_ccw.pressed = false;
        encoder1_ccw.time = (timer_read() | 1);
        action_exec(encoder1_ccw);
    }

    if (IS_PRESSED(encoder1_cw)) {
        encoder1_cw.pressed = false;
        encoder1_cw.time = (timer_read() | 1);
        action_exec(encoder1_cw);
    }

    if (IS_PRESSED(encoder2_ccw)) {
        encoder2_ccw.pressed = false;
        encoder2_ccw.time = (timer_read() | 1);
        action_exec(encoder2_ccw);
    }

    if (IS_PRESSED(encoder2_cw)) {
        encoder2_cw.pressed = false;
        encoder2_cw.time = (timer_read() | 1);
        action_exec(encoder2_cw);
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time = (timer_read() | 1);
            action_exec(encoder1_cw);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time = (timer_read() | 1);
            action_exec(encoder1_ccw);
        }
    } else if (index == 1) {
        if (clockwise) {
            encoder2_cw.pressed = true;
            encoder2_cw.time = (timer_read() | 1);
            action_exec(encoder2_cw);
        } else {
            encoder2_ccw.pressed = true;
            encoder2_ccw.time = (timer_read() | 1);
            action_exec(encoder2_ccw);
        }
    }
    return true;
}

// Defines names for use in layer keycodes and the keymap
enum custom_layers {
    _QWERTY,
    _FN1,
    _FN2,
    _FN3
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QUWERTY Layer */
    [_QWERTY] = LAYOUT(
    /* |--L1---+--L2---+--L3---+--L4---+--L5---+--L6---+--L7---+--L8---+--L9---+|   |--R1---+--R2---+--R3---+--R4---+--R5---+--R6---+--R7---+--R8---+---R9--+--R10--+---R11--+ | */
        KC_ESC, KC_ENT, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                       KC_F8,   KC_F9,  KC_F10, KC_F11, KC_F12,   KC_PSCR,KC_SLCK,KC_PAUS,   LALT(KC_LEFT),
        KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_F6,                       KC_F7,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,   KC_EQL,   KC_BSPC,
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_HOME,                     KC_PGUP, KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,   KC_RBRC,  KC_BSLS,
        KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_END,                      KC_PGDN, KC_H,   KC_J,   KC_K,   KC_L,   LT(_FN2,KC_SCLN),  KC_QUOT,  KC_ENT,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LCTL,                     KC_DEL,  KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,                     KC_RSFT,
      LT(_FN1,KC_LGUI),         KC_LEFT,KC_RGHT,MT(KC_RCTL,KC_SPC), KC_BSPC,  KC_LALT,  LT(_FN3,KC_APP),KC_ENT, MT(KC_RSFT,KC_SPC), KC_UP,  KC_DOWN
    /* |--------+-------+-------+-------+-------+-------+-------+-------+-------+-------|   |--------+-------+-------+-------+-------+-------+-------+-------+-------+-------|*/
    ),

    /*  NUM Pad layer */
    [_FN1] = LAYOUT(
    /* |--L1---+--L2---+--L3---+--L4---+--L5---+--L6---+--L7---+--L8---+--L9---+| */
        KC_RGUI,KC_ENT, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                   KC_F8,   KC_F9,  KC_F10, KC_F11, KC_F12,   KC_PSCR,KC_SLCK,KC_PAUS,   KC_MUTE,
        _______,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_F6,                   KC_F7,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,   KC_EQL,   KC_BSPC,
   LALT(KC_TAB),KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_HOME,                 KC_PGUP, KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,   KC_RBRC,  KC_BSLS,
        _______,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_END,                  KC_PGDN, KC_H,   KC_J,   KC_K,   KC_L,   LT(_FN2,KC_SCLN),  KC_QUOT,  KC_ENT,
        _______,LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V),KC_B,KC_LCTL,        KC_DEL,  KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,                     KC_RSFT,
        _______,        KC_LEFT,KC_RGHT,MT(KC_RCTL,KC_SPC), KC_BSPC, KC_LALT,        LT(_FN3,KC_APP),KC_ENT, MT(KC_RSFT,KC_SPC), KC_UP,  KC_DOWN
     /* |--------+-------+-------+-------+-------+-------+-------+-------+-------+-------|   |--------+-------+-------+-------+-------+-------+-------+-------+-------+-------|*/
),
    /*  Mouse layer */
    [_FN2] = LAYOUT(
    /* |--L1---+--L2---+--L3---+--L4---+--L5---+--L6---+--L7---+--L8---+--L9---+| */
        KC_ESC,KC_AUDIO_MUTE,KC_F1,KC_F2,  KC_F3,   KC_F4,   XXXXXXX,                   KC_F8,   KC_F9,  KC_F10, KC_F11, KC_F12,   KC_PSCR,KC_SLCK,KC_PAUS,   KC_MUTE,
        KC_GRV,  XXXXXXX, KC_ACL0, KC_ACL1,KC_ACL2, XXXXXXX, KC_F6,                        KC_F7,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,   KC_EQL,   KC_BSPC,
        KC_TAB,  KC_WH_L, KC_BTN4, KC_MS_U,KC_BTN5, KC_WH_R, KC_HOME,                      KC_PGUP, KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,   KC_RBRC,  KC_BSLS,
        KC_CAPS, KC_WH_D, KC_MS_L, KC_MS_D,KC_MS_R, KC_WH_U, KC_END,                       KC_PGDN, KC_H,   KC_J,   KC_K,   KC_L,   LT(_FN2,KC_SCLN),  KC_QUOT,  KC_ENT,
        KC_LSFT, KC_Z,    KC_BTN3, KC_BTN1,KC_BTN2, KC_B,    KC_LCTL,                      KC_DEL,  KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,                     KC_RSFT,
      LT(_FN1,KC_LGUI),            KC_LEFT,KC_RGHT,MT(KC_RCTL,KC_SPC),KC_BSPC, KC_LALT,     LT(_FN3,KC_APP),KC_ENT,MT(KC_RSFT,KC_SPC), KC_UP,  KC_DOWN
    /* |--------+-------+-------+-------+-------+-------+-------+-------+-------+-------|   |--------+-------+-------+-------+-------+-------+-------+-------+-------+-------|*/
    ),
    /*  Other layer */
    [_FN3] = LAYOUT(
    /* |--L1---+--L2---+--L3---+--L4---+--L5---+--L6---+--L7---+--L8---+--L9---+| */
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS,  KC_TRNS,KC_TRNS,                        KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                             KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                             KC_HOME, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                             KC_END,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS,                           KC_INS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,                     KC_TRNS,
        KC_TRNS,                KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS,KC_TRNS,           KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
    /* |--------+-------+-------+-------+-------+-------+-------+-------+-------+-------|   |--------+-------+-------+-------+-------+-------+-------+-------+-------+-------|*/
    )
};

