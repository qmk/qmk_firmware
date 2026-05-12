/* Copyright 2024 Cipulot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

// clang-format off
enum layers{
    _MAC_BASE,
    _MAC_FN,
    _WIN_BASE,
    _WIN_FN
};

enum custom_keycodes {
    SNIP = SAFE_RANGE,
};
// clang-format on

#define MAC PDF(_MAC_BASE)
#define WIN PDF(_WIN_BASE)

#define MACFN MO(_MAC_FN)
#define WINFN MO(_WIN_FN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_MAC_BASE] = LAYOUT(
        KC_ESC,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
        MACFN,      KC_LCTL, KC_LOPT,  KC_LCMD,                KC_SPC,                        KC_RCMD,  KC_ROPT,  KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [_MAC_FN] = LAYOUT(
        _______, KC_BRID, KC_BRIU, KC_MCTL, _______,   _______,   _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,  KC_VOLU, SNIP,
        _______, _______, _______, _______, _______,   _______,   _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, WIN,     _______, _______,   _______,   _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______,   _______,   _______, _______, _______, _______, _______, _______,  _______,
        _______, _______, _______, _______, _______,   _______,   NK_TOGG, _______, _______, _______, _______, _______,  RM_VALU,
        _______, _______, _______, _______,                       _______,                   _______, _______, RM_PREV,  RM_VALD,  RM_PREV
    ),
    [_WIN_BASE] = LAYOUT(
        KC_ESC,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
        WINFN,      KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                    KC_RALT, KC_RGUI, KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [_WIN_FN] = LAYOUT(
        _______, KC_BRID, KC_BRIU, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, SNIP,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, NK_TOGG, MAC,     _______, _______, _______, _______, RM_VALU,
        _______, _______, _______, _______,                   _______,                   _______, _______, RM_PREV, RM_VALD, RM_PREV
    ),
    // clang-format on
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SNIP:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_WIN_FN)) {
                    tap_code(KC_PSCR);
                } else if (IS_LAYER_ON(_MAC_FN)) {
                    tap_code16(LSFT(LGUI(KC_3)));
                }
            }
            return false;

        default:
            return true;
    }
}
