 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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
#include "state.h"
#include "luna.h"
#include "oled.h"
#include "encoder.h"

#define L1_SPC LT(1, KC_SPC)
#define L2_ENT LT(2, KC_ENT)
#define L3_ENT LT(3, KC_ENT)

//Default keymap. This can be changed in Via. Use oled.c and encoder.c to change beavior that Via cannot change.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERT */

[0] = LAYOUT(
   KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,   KC_GRV,
   KC_ESC,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_BSPC,
   KC_TAB,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_QUOT,
  KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,  KC_MUTE,  XXXXXXX,     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,  KC_RSFT,
                      KC_LGUI,  KC_LALT, KC_LCTRL,   L1_SPC,   L2_ENT,   KC_SPC,    MO(3), KC_RCTRL,  KC_RALT,  KC_RGUI
),
/* YUIOP */
[1] = LAYOUT(
   KC_DEL,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,   KC_GRV,
  KC_BSPC,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,                         KC_J,     KC_L,     KC_U,     KC_Y,  KC_SCLN,  KC_BSPC,
  KC_QUOT,     KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,                         KC_H,     KC_N,     KC_E,     KC_I,     KC_O,  KC_QUOT,
  KC_RSFT,     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,  KC_MPLY,  XXXXXXX,     KC_K,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,  KC_RSFT,
                      KC_LGUI,  KC_LALT, KC_LCTRL,  _______,   L3_ENT,   KC_SPC,  _______, KC_RCTRL,  KC_RALT,  KC_RGUI
),
/* FUNCTION */
[2] = LAYOUT(
  _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                        KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,
  _______,  XXXXXXX,    KC_UP,  XXXXXXX,  KC_LBRC,  KC_RBRC,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   KC_F12,
  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,  KC_BSLS,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MINS,   KC_EQL,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                      _______,  _______,  _______,    TG(0),  _______,  _______,  _______,  _______,  _______, _______
),
/* KEYBOARD CONTROL */
[3] = LAYOUT(
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                      XXXXXXX,  XXXXXXX,  XXXXXXX,    TG(3),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
            /* Smart Backspace Delete */
        case KC_RSFT:
        case KC_LSFT:
            // Set shift status for other modules to use.
            shift_held = record->event.pressed;
            held_shift = keycode;
            break;
        case KC_LCTL:
        case KC_RCTL:
            update_luna_sneaking(record->event.pressed);
            break;
        case KC_SPC:
            update_luna_jump(record->event.pressed);
            break;
    }
    return true;
}
