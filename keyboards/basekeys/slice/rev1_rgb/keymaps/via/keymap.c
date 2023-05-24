/* Copyright 2020 2Moons
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
#include "split_util.h"
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY,
  _FN,
  _LOWER,
  _RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_all(
  //,------------------------------------------------------------------------|   |---------------------------------------------------------------------------.
       KC_ESC, KC_GRAVE,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,        KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL,      KC_BSPACE,
  //|------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
       RGB_MODE_FORWARD,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC,   KC_RBRC,   KC_BSLS,
  //|------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
      RGB_MODE_GRADIENT, KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,        KC_ENT,
  //|------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
          RGB_MODE_XMAS, KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,   KC_RSFT,   KC_RSFT,
  //|------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
                RGB_TOG, KC_LCTL, KC_LALT, KC_LALT,  KC_SPC,  KC_SPC,  KC_SPC,      KC_SPC,  KC_SPC,                            KC_RALT,   KC_RCTL,   MO(_FN)
  //`------------------------------------------------------------------------|   |---------------------------------------------------------------------------'
  ),

  [_FN] = LAYOUT_all(
  //,-------------------------------------------------------------------------|   |---------------------------------------------------------------------------.
       KC_ESC,  KC_GRAVE,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,      KC_BSPACE,
  //|-------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
      _______,            _______, _______, _______, _______, _______, _______,     _______, KC_PSCR, KC_SLCK, KC_PAUSE,  KC_UP, _______,   _______,   _______,
  //|-------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
      _______,            _______, _______, _______, _______, _______, _______,     _______, KC_HOME, KC_PGUP, KC_LEFT,KC_RIGHT, _______,       _______,
  //|-------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
      _______,            _______, _______, _______, _______, _______, _______,     _______,  KC_END, KC_PGDN, KC_DOWN, _______, _______,   _______,   _______,
  //|-------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
      _______,            _______, _______, _______, _______, _______, _______,     _______, _______,                            _______,   _______,   _______
  //`-------------------------------------------------------------------------|   |---------------------------------------------------------------------------'
  ),

  [_LOWER] = LAYOUT_all(
  //,------------------------------------------------------------------------|   |---------------------------------------------------------------------------.
       KC_ESC, KC_GRAVE,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,        KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL,      KC_BSPACE,
  //|------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
       RGB_MODE_FORWARD,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC,   KC_RBRC,   KC_BSLS,
  //|------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
      RGB_MODE_GRADIENT, KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,        KC_ENT,
  //|------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
          RGB_MODE_XMAS, KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,   KC_RSFT,   KC_RSFT,
  //|------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
                RGB_TOG, KC_LCTL, KC_LALT, KC_LALT,  KC_SPC,  KC_SPC,  KC_SPC,      KC_SPC,  KC_SPC,                            KC_RALT,   KC_RCTL,   MO(_FN)
  //`------------------------------------------------------------------------|   |---------------------------------------------------------------------------'
  ),

  [_RAISE] = LAYOUT_all(
  //,------------------------------------------------------------------------|   |---------------------------------------------------------------------------.
       KC_ESC, KC_GRAVE,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,        KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL,      KC_BSPACE,
  //|------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
       RGB_MODE_FORWARD,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC,   KC_RBRC,   KC_BSLS,
  //|------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
      RGB_MODE_GRADIENT, KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,        KC_ENT,
  //|------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
          RGB_MODE_XMAS, KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,   KC_RSFT,   KC_RSFT,
  //|------------------+--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+----------+----------|
                RGB_TOG, KC_LCTL, KC_LALT, KC_LALT,  KC_SPC,  KC_SPC,  KC_SPC,       KC_SPC,  KC_SPC,                            KC_RALT,   KC_RCTL,   MO(_FN)
  //`------------------------------------------------------------------------|   |---------------------------------------------------------------------------'
  )
};

#ifdef OLED_ENABLE

static void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(qmk_logo, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return isLeftHand ? OLED_ROTATION_180 : OLED_ROTATION_0;
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
    case _QWERTY:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case _FN:
      oled_write_P(PSTR("Function\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
  } else {
    render_qmk_logo();
  }
    return false;
}
#endif
