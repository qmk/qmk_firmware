/* Copyright 2024 lostdotfish
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
* along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.
*/

#include QMK_KEYBOARD_H


enum orbweaver_layers {
  _DEFAULT,
  _LETTERS,
  _CONTROL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//generic default keymap with Razor defaults (+ 20 shifts layer)

     [_DEFAULT] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F,
        KC_LSFT, KC_Z, KC_X, KC_C, TO(1),
        KC_LALT, KC_UP, KC_DOWN, KC_RIGHT, KC_LEFT,
        KC_SPACE
    ),

//Second example keymap with all modifier keys replaced with numbers or letters
     
   [_LETTERS] = LAYOUT(
        KC_0, KC_1, KC_2, KC_3, KC_4,
        KC_I, KC_Q, KC_W, KC_E, KC_R,
        KC_J, KC_A, KC_S, KC_D, KC_F,
        KC_K, KC_Z, KC_X, KC_C, TO(2),
        KC_L, KC_UP, KC_DOWN, KC_RIGHT, KC_LEFT,
        KC_SPACE
    ),

//, RGB Contol Keymap
   [_CONTROL] = LAYOUT(
        RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU,
        RM_PREV, RM_HUED, RM_SATD, RM_VALD, RM_SPDD,
        RM_TOGG, KC_A, KC_S, KC_D, KC_F,
        KC_K, KC_Z, KC_X, KC_C, TO(0),
        KC_L, KC_UP, KC_DOWN, KC_RIGHT, KC_LEFT,
        KC_SPACE
    ) 

};

layer_state_t layer_state_set_user(layer_state_t state) {
    gpio_write_pin_high(GP23);
    gpio_write_pin_high(GP24);
    gpio_write_pin_high(GP25);
    switch (get_highest_layer(state)) {
        case _DEFAULT:
            gpio_write_pin_low(GP23);
            break;
        case _LETTERS:
            gpio_write_pin_low(GP25);
            break;
        case _CONTROL:
            gpio_write_pin_low(GP24);
            break;
    }
    return state;
}
void suspend_power_down_kb(void) {
    // code will run multiple times while keyboard is suspended
    gpio_write_pin_high(GP23);
    gpio_write_pin_high(GP24);
    gpio_write_pin_high(GP25);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    layer_state_set_kb(layer_state);
    suspend_wakeup_init_user();
}
