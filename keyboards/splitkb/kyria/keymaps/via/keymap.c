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

enum layers { _QWERTY = 0, _LOWER, _RAISE, _ADJUST };

// clang-format off

#define LAYOUT_via( \
    L00, L01, L02, L03, L04, L05, LE0, LE1, RE0, RE1, R06, R07, R08, R09, R10, R11, \
    L12, L13, L14, L15, L16, L17,                     R18, R19, R20, R21, R22, R23, \
    L24, L25, L26, L27, L28, L29, L30, L31, R32, R33, R34, R35, R36, R37, R38, R39, \
                   L40, L41, L42, L43, L44, R45, R46, R47, R48, R49 \
) \
{ \
    { LE0,   LE1,   L05,   L04,   L03,   L02,   L01,   L00   }, \
    { RE0,   RE1,   L17,   L16,   L15,   L14,   L13,   L12   }, \
    { L31,   L30,   L29,   L28,   L27,   L26,   L25,   L24   }, \
    { L44,   L43,   L42,   L41,   L40,   KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, R06,   R07,   R08,   R09,   R10,   R11   }, \
    { KC_NO, KC_NO, R18,   R19,   R20,   R21,   R22,   R23   }, \
    { R32,   R33,   R34,   R35,   R36,   R37,   R38,   R39   }, \
    { R45,   R46,   R47,   R48,   R49,   KC_NO, KC_NO, KC_NO }, \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_via(
      LT(_RAISE, KC_ESC),      KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_VOLD, KC_VOLU,   KC_PGDN, KC_PGUP, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PIPE,
      MT(MOD_LCTL, KC_BSPC),   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT,                 KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LSFT, KC_LSFT,   KC_LSFT, KC_LSFT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                                KC_LGUI, KC_DEL, MT(MOD_LALT, KC_ENT), KC_SPC,  FN_MO13,   FN_MO23, KC_ENT,  KC_TAB,  KC_BSPC, KC_RALT
    ),
    [_LOWER] = LAYOUT_via(
      _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS,
      _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                      KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, _______, _______, KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                                 _______, _______, _______, KC_EQL,  KC_EQL,  KC_SCLN,  KC_SCLN, _______, _______, _______
    ),
    [_RAISE] = LAYOUT_via(
      _______, KC_1, 	  KC_2,    KC_3,    KC_4,    KC_5,  _______, _______, _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
      _______, _______, _______, _______, KC_MUTE, KC_VOLD, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_ADJUST] = LAYOUT_via(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, _______, _______, KC_F11,  KC_F12,  _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};
// clang-format on

static uint8_t  encoder_state[2] = {0};
static keypos_t encoder_cw[2]    = {{0, 0}, {0, 1}};
static keypos_t encoder_ccw[2]   = {{1, 0}, {1, 1}};

void encoder_action_unregister(void) {
    for (int index = 0; index < 2; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t){.key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index], .pressed = false, .time = (timer_read() | 1)};
            encoder_state[index]     = 0;
            action_exec(encoder_event);
        }
    }
}

void encoder_action_register(uint8_t index, bool clockwise) {
    keyevent_t encoder_event = (keyevent_t){.key = clockwise ? encoder_cw[index] : encoder_ccw[index], .pressed = true, .time = (timer_read() | 1)};
    encoder_state[index]     = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

void matrix_scan_kb(void) {
    encoder_action_unregister();
    matrix_scan_user();
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    return false;
};
