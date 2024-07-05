/* Copyright 2017 Fabian Topfstedt
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

enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
};

#define LT1_SPC LT(_LOWER,KC_SPC)
#define LT2_SPC LT(_RAISE,KC_SPC)
#define LT3_LGU LT(_ADJUST,KC_LGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Default Layer
     * ,-----------------------------------------------.
     * |Esc| Q | W | E | R | T | Y | U | I | O | P |BS |
     * |-----------------------------------------------|
     * |Tab | A | S | D | F | G | H | J | K | L |Enter |
     * |-----------------------------------------------|
     * | LSft | Z | X | C | V | B | N | M | , | .  |/? |
     * |-----------------------------------------------|
     * |LCtl|GUI|LAlt|Spc/Fn0 | Spc/Fn1  |Fn2 |Alt|RCtl|
     * `-----------------------------------------------'
     */
    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,             KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        KC_LCTL, KC_LGUI, KC_LALT,                   LT1_SPC, LT2_SPC,                   LT3_LGU, KC_RALT, KC_RCTL
    ),

    /* Function Layer 1 HHKB style
     * ,-----------------------------------------------.
     * | ~ | ! | @ | # | $ | % | ^ | & | * | ( | ) |BS |
     * |-----------------------------------------------|
     * | F1 |F2 |F3 |F4 |F5 |F6 | _ | + | { | } | Pipe |
     * |-----------------------------------------------|
     * |  F7  |F8 |F9 |F10|F11|F12| ~ | | |BL±|BL+ |BL-|
     * |-----------------------------------------------|
     * |    |   |    |        |   Left   |Down|Up |Rght|
     * `-----------------------------------------------'
     */
    [_LOWER] = LAYOUT(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS,    KC_LCBR,    KC_RCBR,          KC_PIPE,
        KC_F7,            KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), BL_TOGG, BL_UP,   BL_DOWN,
        _______, _______, _______,                   _______, KC_LEFT,                         KC_DOWN, KC_UP,   KC_RGHT
    ),

    /* Function Layer 1 HHKB style
     * ,-----------------------------------------------.
     * | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 |BS |
     * |-----------------------------------------------|
     * | F1 |F2 |F3 |F4 |F5 |F6 | - | = | [ | ] |  \   |
     * |-----------------------------------------------|
     * |  F7  |F8 |F9 |F10|F11|F12| # | \ |   |    |Del|
     * |-----------------------------------------------|
     * |    |   |    |        |          |    |   |RGB±|
     * `-----------------------------------------------'
     */
    [_RAISE] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,          KC_BSLS,
        KC_F7,            KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, KC_DEL,
        _______, _______, _______,                   _______, _______,                   _______, _______, RGB_TOG
    ),

    /* Function Layer 1 HHKB style
     * ,-----------------------------------------------.
     * |   |RST|   |   |   |   |   |   |   |   |   |Del|
     * |-----------------------------------------------|
     * |    |   |   |Au1|Au0|AGN|AGS|   |   |   |      |
     * |-----------------------------------------------|
     * |      |   |   |RTg|RMd|RH+|RH-|RS+|RS-|RV+ |RV-|
     * |-----------------------------------------------|
     * |SLP |   |    |        |          |    |   |RTg |
     * `-----------------------------------------------'
     */
    [_ADJUST] = LAYOUT(
        _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
        _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______,          _______,
        _______,          _______, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD,
        KC_SLEP, _______, _______,                   _______, _______,                   _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
    }
    return true;
}
