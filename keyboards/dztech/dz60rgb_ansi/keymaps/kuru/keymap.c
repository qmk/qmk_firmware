/* Copyright 2022 Murali Suresh
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_ansi(
        KC_GRAVE,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, LT(2,KC_BSLS),
        CTL_T(KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_UP,
        KC_LCTL,        KC_LGUI, KC_LALT,                            KC_SPC,                             MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_60_ansi(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, KC_UP,   _______, _______, _______, KC_CALC, _______, KC_INS,  _______, KC_PSCR, KC_SLCK, KC_PAUS, RESET,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP,          _______,
        KC_MPRV,          KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, NK_TOGG, _______, _______, KC_END,  KC_PGDN,          KC_MNXT,
        _______, _______, _______,                            TO(3)  ,                            _______, _______, _______, _______
    ),
    [2] = LAYOUT_60_ansi(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, RGB_TOG, _______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_MOD, _______, _______, _______, RESET,
        _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPI, RGB_SPD, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),
    [3] = LAYOUT_60_ansi(
        KC_GRAVE,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  LT(4,KC_BSPC),
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        CTL_T(KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        MO(4)  ,        KC_LGUI, KC_RALT,                            KC_SPC,                             KC_RALT, KC_RGUI, MO(2),   KC_RCTL
    ),
    [4] = LAYOUT_60_ansi(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, _______, KC_END,  _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, RESET,
        _______, KC_HOME, _______, _______, KC_PGDN, _______, KC_LEFT, KC_DOWN, KC_UP ,  KC_RGHT, _______, _______,          _______,
        _______,          _______, _______, _______, _______, KC_PGUP, NK_TOGG, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            TO(0)  ,                            _______, _______, _______, _______
    ),
};

void highlight_layer3(void){
    // F9-F12
    rgb_matrix_set_color(4, 0xFF, 0xFF, 0xFF);
    rgb_matrix_set_color(3, 0xFF, 0xFF, 0xFF);
    rgb_matrix_set_color(2, 0xFF, 0xFF, 0xFF);
    rgb_matrix_set_color(1, 0xFF, 0xFF, 0xFF);
    // F1-F4
    rgb_matrix_set_color(9, 0xFF, 0xFF, 0xFF);
    rgb_matrix_set_color(10, 0xFF, 0xFF, 0xFF);
    rgb_matrix_set_color(11, 0xFF, 0xFF, 0xFF);
    rgb_matrix_set_color(12, 0xFF, 0xFF, 0xFF);
    // Reset
    rgb_matrix_set_color(14, 0x99, 0x99, 0xFF);
    // Pause + Slck + PrScr
    rgb_matrix_set_color(15, 0xFF, 0x99, 0x00);
    rgb_matrix_set_color(16, 0xFF, 0x99, 0x00);
    rgb_matrix_set_color(17, 0xFF, 0x99, 0x00);
    // Pgup, Home
    rgb_matrix_set_color(39, 0x00, 0x99, 0x00);
    rgb_matrix_set_color(24, 0x00, 0x99, 0x00);
    // hjkl
    rgb_matrix_set_color(31, 0x00, 0x00, 0xFF);
    rgb_matrix_set_color(32, 0x00, 0x00, 0xFF);
    rgb_matrix_set_color(33, 0x00, 0x00, 0xFF);
    rgb_matrix_set_color(34, 0x00, 0x00, 0xFF);
    // PgDwn, End
    rgb_matrix_set_color(36, 0x00, 0x99, 0x00);
    rgb_matrix_set_color(46, 0x00, 0x99, 0x00);
}

void rgb_matrix_indicators_user(void) {
	  uint8_t this_led = host_keyboard_leds();
      if (!g_suspend_state) {
        switch (get_highest_layer(layer_state)) {
          case 3:
            highlight_layer3(); break;
          default:
            break;
        }
      }
	  if ( this_led & (1<<USB_LED_CAPS_LOCK)) {
	        rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF);
	  }
}
