/* Copyright 2018 takashiski
 * Copyright 2019 kakunpc
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

enum layers{
    DF,
    LW,
    FN
};


#define LT_F13 LT(FN, KC_F13)
#define LT_F14 LT(FN, KC_F14)
#define KC_LW MO(LW)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DF]=LAYOUT(
            KC_ESC,KC_GRV,KC_1,KC_2,KC_3,KC_4,KC_5,                 KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINS,KC_EQL,KC_BSPC,
            KC_TAB  ,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,                 KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRC,KC_RBRC,KC_BSLS,
            KC_LCTL ,KC_A,KC_S,KC_D,KC_F,KC_G,                     KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT,KC_ENT,
            KC_LSFT   ,KC_Z,KC_X,KC_C,KC_V,KC_B,                    KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,KC_DEL,
            KC_LGUI,KC_NO,KC_LALT,KC_LW,LT_F13,KC_SPC,               KC_SPC,LT_F14,KC_LEFT,KC_UP,KC_DOWN,KC_RIGHT
            ),
    [LW]=LAYOUT(
            RGB_TOG,KC_NO,RGB_VAD,RGB_VAI,RGB_HUI,RGB_HUD,KC_TRNS,    RGB_MOD,RGB_RMOD,KC_TRNS,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
            KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,              KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
            KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
            KC_NO   ,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                 KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
            KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO
            ),
    [FN]=LAYOUT(
            KC_ESC,KC_GRV,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,            KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_BSPC,
            KC_TAB  ,KC_NO,KC_UP,KC_NO,KC_NO,KC_NO,KC_NO,           KC_7,KC_8,KC_0,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
            KC_LCTL ,KC_LEFT,KC_DOWN,KC_RIGHT,KC_NO,KC_NO,         KC_4,KC_5,KC_6,KC_NO,KC_NO,KC_NO,KC_NO,
            KC_LSFT   ,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,               KC_1,KC_2,KC_3,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
            KC_LGUI,KC_NO,KC_LALT,KC_INT5,KC_NO,KC_SPC,             KC_0,KC_NO,KC_HOME,KC_PGUP,KC_PGDN,KC_END
            ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void keyboard_post_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
