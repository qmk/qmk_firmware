/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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
#include "v60_type_r.h"

#define _____ KC_TRNS
#define XXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|   Bs  |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |FN0   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
     * |-----------------------------------------------------------|
     * |LShift  |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| RShift   |
     * |-----------------------------------------------------------|
     * |Ctrl|Alt |Gui |      Space/L3           |Gui |Alt |Ctrl|Fn1|
     * `-----------------------------------------------------------'
     */
    [0] = KEYMAP(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXX, KC_BSPC, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,     KC_BSLS, \
        LT(1, KC_CAPS),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  \
        KC_LSFT, XXXXX,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, XXXXX,  \
        KC_LCTL, KC_LALT, KC_LGUI,               LT(2, KC_SPC),                          KC_RGUI, KC_RALT,  KC_RCTL, MO(3)),
    /* Keymap 1: FN Layer
     * ,-----------------------------------------------------------.
     * |`  | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|  Del  |
     * |-----------------------------------------------------------|
     * |     |   |   |   |   |   |   |   |   |   |PSc|SLk|Pau| Ins |
     * |-----------------------------------------------------------|
     * |      |   |   |   |   |   | Lt| Dn| Up| Rt|Hom|PgU|        |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |Mut|VDn|VUp|End|PgD|          |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |    |    |    |    |
     * `-----------------------------------------------------------'
     */
    [1] = KEYMAP(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  _____,  KC_DEL, \
        _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____, KC_PSCR, KC_SLCK, KC_PAUS,          KC_INS, \
        _____,   _____,   _____,   _____,   _____,   _____, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_HOME, KC_PGUP,           _____,          \
        _____,   _____,   _____,   _____,   _____,   _____,   _____, KC_MUTE, KC_VOLD, KC_VOLU,  KC_END, KC_PGDN,           _____,  _____,  \
        _____,   _____,   _____,               _____,                                                      _____,   _____,  _____,  _____),
    /* Keymap 2: Mouse Keys Layer
     * ,-----------------------------------------------------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |
     * |-----------------------------------------------------------|
     * |     |   |   |   |   |   |   |MWU|MWD|   |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |   |   |   |   |   |MLt|MDn|MUp|MRt|   |   |        |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |SPC|Ms1|Ms2|Ms3|   |   |          |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |    |    |    |    |
     * `-----------------------------------------------------------'
     */
    [2] = KEYMAP(
        _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,  _____,  _____,  _____,  _____,  _____, \
        _____,   _____,   _____,   _____,   _____,   _____,   _____,   KC_MS_WH_UP, KC_MS_WH_DOWN,   _____, _____, _____, _____,          _____, \
        _____,   _____,   _____,   _____,   _____,   _____, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, _____, _____,           _____,          \
        _____,   _____,   _____,   _____,   _____,   _____,   KC_SPC, KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3,  _____, _____,           _____,  _____,  \
        _____,   _____,   _____,               _____,                                                      _____,   _____,  _____,  _____),
    /* Keymap 3: LED Modification Layer
     * ,-----------------------------------------------------------.
     * |   |BLT|BLC|UGT|UGP|UGB|UGR|   |   |   |   |   |   |       |
     * |-----------------------------------------------------------|
     * |     |RD+|GN+|BL+|HU+|SA+|VA+|   |   |   |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |RD-|GN-|BL-|HU-|SA-|VA-|   |   |   |   |   |        |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |   |   |   |   |   |          |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |    |    |    |    |
     * `-----------------------------------------------------------'
     */
    [3] = KEYMAP(
        _____, BL_TOGG, BL_STEP, RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_R,   _____,   _____,   _____,   _____,   _____,   _____,  _____,  _____, \
        _____, RGB_RI,  RGB_GI,  RGB_BI,  RGB_HUI, RGB_SAI, RGB_VAI,   _____,   _____,   _____,   _____,   _____,   _____,          _____, \
        _____, RGB_RD,  RGB_GD,  RGB_BD,  RGB_HUD, RGB_SAD, RGB_VAD,   _____,   _____,   _____,   _____,   _____,           _____,          \
        _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,           _____,  _____,  \
        _____,   _____,   _____,               _____,                                                      _____,   _____,  _____,  _____),
};

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // output low
        DDRE  |=  (1<<PE6);
        PORTE &= ~(1<<PE6);
    }
    else {
        // Hi-Z
        DDRE  &= ~(1<<PE6);
        PORTE &= ~(1<<PE6);
    }
}
