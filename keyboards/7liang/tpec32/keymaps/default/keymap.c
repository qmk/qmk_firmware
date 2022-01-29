/* Copyright 2022 Se1enLiang(@skyjun)
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
    _L1,
    _L2,
    _L3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_3x12(
    // ,-----------------------------------------------------------------------------------------------------------------------------------------.
         KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,                                  KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,
    // |----------|----------|----------|----------|----------|         [    ]            |----------|----------|----------|----------|----------|
         KC_A,      KC_S,      KC_D,    LT(3, KC_F), LT(2, KC_G),                           KC_H,      KC_J,      KC_K,      KC_L,      KC_ENT,
    // |----------|----------|----------|----------|----------|-----------,---------------|----------|----------|----------|----------|----------|
         KC_Z,      KC_X, MT(MOD_LSFT, KC_C), KC_V,  LT(1, KC_B),  KC_BTN1,   KC_BTN2,      KC_N,      KC_M,      KC_RSFT,   KC_SPC,    KC_BSPC
    // `-----------------------------------------------------------------------------------------------------------------------------------------'
    ),

    [_L1] = LAYOUT_ortho_3x12(
    // ,-----------------------------------------------------------------------------------------------------------------------------------------.
         KC_1,      KC_2,      KC_3,      KC_4,      KC_5,                                  KC_6,      KC_7,      KC_8,      KC_9,      KC_0,
    // |----------|----------|----------|----------|----------|         [    ]            |----------|----------|----------|----------|----------|
         KC_6,      KC_7,      KC_8,      KC_9,      KC_0,                                  KC_LBRC,   KC_MINS,   KC_BSLS,   KC_SCLN,   KC_QUOT,
    // |----------|----------|----------|----------|----------|-----------,---------------|----------|----------|----------|----------|----------|
         KC_GRV,    _______,   _______,   _______,   _______,   KC_BTN3,    KC_BTN4,        KC_RBRC,   KC_EQL,    KC_COMM,   KC_DOT,    KC_SLSH
    // `-----------------------------------------------------------------------------------------------------------------------------------------'
    ),
         
    [_L2] = LAYOUT_ortho_3x12(
    // ,-----------------------------------------------------------------------------------------------------------------------------------------.
         KC_ESC,    _______,   _______,   _______,   _______,                               _______,   _______,   _______,   _______,   _______,
    // |----------|----------|----------|----------|----------|         [    ]            |----------|----------|----------|----------|----------|
         KC_TAB,    KC_CAPS,   _______,   _______,   _______,                               KC_LEFT,   KC_DOWN,   KC_UP,     KC_RGHT,   _______,
    // |----------|----------|----------|----------|----------|-----------,---------------|----------|----------|----------|----------|----------|
         KC_LCTL,   KC_LWIN,   _______,   KC_LALT,   _______,   KC_BTN1,    KC_BTN2,        KC_RALT,   KC_RCTL,   _______,   _______,   KC_DEL
    // `-----------------------------------------------------------------------------------------------------------------------------------------'
    ),
         
    [_L3] = LAYOUT_ortho_3x12(
    // ,-----------------------------------------------------------------------------------------------------------------------------------------.
         KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,                                 KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,
    // |----------|----------|----------|----------|----------|         [    ]            |----------|----------|----------|----------|----------|
         C(KC_A),   C(KC_S),   _______,   _______,   _______,                               _______,   _______,   _______,   KC_F11,    KC_F12,
    // |----------|----------|----------|----------|----------|-----------,---------------|----------|----------|----------|----------|----------|
         C(KC_Z),   C(KC_X),   C(KC_C),   C(KC_V),   _______,   RGB_TOG,    RGB_MOD,        _______,   _______,   _______,   _______,   RESET
    // `-----------------------------------------------------------------------------------------------------------------------------------------'
    )
};


bool encoder_update_user(bool clockwise)
{
    if (IS_LAYER_ON(_BASE))
    {
        if (clockwise) tap_code(KC_WH_U);
        else tap_code(KC_WH_D);
    } else if (IS_LAYER_ON(_L1))
    {
        if (clockwise) tap_code(KC_VOLU);
        else tap_code(KC_VOLD);
    } else if (IS_LAYER_ON(_L2))
    {
        if (clockwise) tap_code(KC_HOME);
        else tap_code(KC_END);
    } else if (IS_LAYER_ON(_L3))
    {
        if (clockwise) tap_code(KC_PGUP);
        else tap_code(KC_PGDN);
    }

    return true;
}
