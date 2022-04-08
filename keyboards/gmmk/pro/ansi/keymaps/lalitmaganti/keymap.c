/* Copyright 2021 Lalit Maganti

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#ifdef PROGRAMMABLE_BUTTON_ENABLE
#define L1_NUM1 PROGRAMMABLE_BUTTON_1
#define L1_NUM2 PROGRAMMABLE_BUTTON_2
#define L1_NUM3 PROGRAMMABLE_BUTTON_3
#define L1_NUM4 PROGRAMMABLE_BUTTON_4
#define L1_NUM5 PROGRAMMABLE_BUTTON_5
#define L1_NUM6 PROGRAMMABLE_BUTTON_6
#define L1_NUM7 PROGRAMMABLE_BUTTON_7
#define L1_NUM8 PROGRAMMABLE_BUTTON_8
#define L1_NUM9 PROGRAMMABLE_BUTTON_9
#else
#define L1_NUM1 _______
#define L1_NUM2 _______
#define L1_NUM3 _______
#define L1_NUM4 _______
#define L1_NUM5 _______
#define L1_NUM6 _______
#define L1_NUM7 _______
#define L1_NUM8 _______
#define L1_NUM9 _______
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_END,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGUP,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24, RGB_TOG,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code_delay(KC_VOLU, 10);
    } else {
      tap_code_delay(KC_VOLD, 10);
    }
    return false;
}


#ifdef RGB_MATRIX_ENABLE

static void set_rgb_side_leds(void);

static void set_rgb_side_leds() {
    rgb_matrix_set_color(67, RGB_WHITE); // Left side LED 1
    rgb_matrix_set_color(68, RGB_WHITE); // Right side LED 1
    rgb_matrix_set_color(91, RGB_WHITE); // Left side LED 8
    rgb_matrix_set_color(92, RGB_WHITE); // Right side LED 8
}

void rgb_matrix_indicators_user() {
    rgb_matrix_set_color_all(0x0, 0x0, 0x0);
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(3, RGB_WHITE); // CAPS
    }
    set_rgb_side_leds();
}

#endif