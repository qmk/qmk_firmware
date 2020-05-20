/* Copyright 2020 klackygears
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
#include "klackygears.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  [_MACBASE] = LAYOUT_wrapper( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, _______,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TO(_WINBASE),
    _______________DVORAK_L1___________________, _______, LCTL(KC_LEFT), LCTL(KC_UP), LCTL(KC_RIGHT), _______, _______________DVORAK_R1___________________,
    _______________DVORAK_L2___________________, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______________DVORAK_R2___________________,
    _______________MACDVK_L3___________________, _______, _______, _______, _______, _______, _______________MACDVK_R3___________________,
    _______, _______, ________MAC_THUMB_L______, _______, RGB_MOD, _______, _______, ________MAC_THUMB_R______, _______, _______, _______
  ),


  [_WINBASE] = LAYOUT_wrapper( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TO(_GAMER),
    _______________DVORAK_L1___________________, _______, LCTL(KC_TAB), LGUI(KC_TAB), LCTL(LSFT(KC_TAB)), _______, _______________DVORAK_R1___________________,
    _______________DVORAK_L2___________________, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______________DVORAK_R2___________________,
    _______________WINDVK_L3___________________, _______, KC_PGUP, KC_UP,   KC_PGDN, _______, _______________WINDVK_R3___________________,
    RGB_TOG, _______, ________WIN_THUMB_L______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, ________WIN_THUMB_R______, _______, _______
  ),


  [_QWERTY] = LAYOUT_wrapper( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  _________________QWERTY_L1_________________,  LCTL(KC_LEFT), LCTL(KC_UP), LCTL(KC_RIGHT), _________________QWERTY_R1_________________, KC_BSLS,
    KC_CAPS, _________________QWERTY_L2_________________,  KC_MUTE, KC_VOLD, KC_VOLU,   _________________QWERTY_R2_________________, KC_ENT,
    KC_LSFT, _________________QWERTY_L3_________________,  KC_PGUP, KC_UP,   KC_PGDN,   _________________QWERTY_R3_________________, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LGUI, LT(_MNMB, KC_SPC), LT(_SYMB, KC_SPC),  KC_SPC, MO(_NUMB), MO(_NUMB), MO(_FUNC), KC_SPC, LT(_SYMB, KC_SPC), KC_LEFT, KC_UP, KC_DOWN, KC_RGHT
  ),


  [_GAMER] = LAYOUT_wrapper( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL, KC_6,    KC_7,    KC_8,    KC_9,    KC_0, TO(_WINBASE),
    KC_TAB,  KC_R,    KC_Q,    KC_W,    KC_E,    KC_1,    _______, LSFT(KC_F2), _______, _______, _______, _______, _______, _______, _______,
    KC_LCTL, KC_F,    KC_A,    KC_S,    KC_D,    KC_2,    _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_LSFT, _______, KC_X,    KC_Z,    KC_C,    KC_3,    KC_M,    _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_LCTL, KC_LALT, KC_LCTL, KC_LSFT, KC_SPC,  KC_SPC,  _______, _______, _________________KC_BLANK__________________, MO(_FUNC)
  ),


  [_SYMB] = LAYOUT_wrapper( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NLCK, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _________________PUNC_L1_ALT_______________, _______, KC_P7,   KC_P8,   KC_P9,  _______, _________________PUNC_R1___________________,
    _________________PUNC_L3___________________, _______, KC_P4,   KC_P5,   KC_P6,  _______, _________________PUNC_R2___________________,
    _________________PUNC_L3_ALT_______________, _______, KC_P1,   KC_P2,   KC_P3,  _______, _________________PUNC_R3___________________,
    _______, _______, _______, _______, KC_DEL, _________________KC_BLANK__________________, KC_CAPS, _______, _______, _______, _______
  ),


  [_FUNC] = LAYOUT_wrapper( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NLCK, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _____________FUNC_L1_______________________, _______, _______, _______, _______, _______, _______, _____________FUNC_1_______________,
    ________MAC_MISSION_CTRL__________, _______, LGUI(KC_L), _______, _______, _______, _______, _______, _____________FUNC_2_______________,
    _____________FUNC_L3_______________________, _______, _______, _______, _______, KC_GRV,  _______, _____________FUNC_3_______________,
    _________________KC_BLANK__________________, _________________KC_BLANK__________________, KC_CAPS, _______, _______, _______, _______
  ),


  [_MNMB] = LAYOUT_wrapper( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_MINS, KC_PLUS, KC_QUES,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    _________________MACNAV_L1_________________, _______, _______, _______, _______, _______, _________________NUMB_R1___________________,
    _________________MACNAV_L2_________________, _______, _______, _______, _______, _______, _________________NUMB_R2___________________,
    _________________MACNAV_L3_________________, _______, _______, _______, _______, _______, _________________NUMB_R3_MAC_______________,
    _________________KC_BLANK__________________, _________________KC_BLANK__________________, KC_RSFT, _______, _______, _______, _______
  ),


  [_NUMB] = LAYOUT_wrapper( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_MINS, KC_PLUS, KC_QUES,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    _________________WINNAV_L1_________________, _______, _______, _______, _______, _______, _________________NUMB_R1___________________,
    _________________WINNAV_L2_________________, _______, _______, _______, _______, _______, _________________NUMB_R2___________________,
    _________________WINNAV_L3_________________, _______, _______, _______, _______, _______, _________________NUMB_R3_WIN_______________,
    _________________KC_BLANK__________________, _________________KC_BLANK__________________, KC_RSFT, _______, _______, _______, _______
  ),


  [_MDIA] = LAYOUT_wrapper( \
    _________________KC_BLANK__________________, _________________KC_BLANK__________________, _________________KC_BLANK__________________,
    _________________LYOUT_____________________, _______, _______, _______, _______, _______, _________________RGB_1_____________________,
    _________________KC_BLANK__________________, _______, _______, _______, _______, _______, _________________RGB_2_____________________,
    _________________KC_BLANK__________________, _______, _______, _______, _______, _______, _________________MEDIA_____________________,
    _________________KC_BLANK__________________, _________________KC_BLANK__________________, _________________KC_BLANK__________________
  )

};




// void matrix_init_user(void) {


// }

#ifdef RGBLIGHT_EFFECT_SNAKE
__attribute__ ((weak))
const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {35, 25, 15};
#endif

#ifdef RGBLIGHT_EFFECT_KNIGHT
__attribute__ ((weak))
const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {35, 29, 17};
#endif

 void matrix_scan_user(void) {

   /* switch(biton32(layer_state)) {
      case _GAMER:
        rgblight_setrgb(0xF4,  0x03, 0xFC);
      break;
      case _NUMB:
        rgblight_setrgb_at(RGB_BLUE, 43);
      break;
    }*/

 }

 void led_set_user(uint8_t usb_led) {
 //  rgblight_set_clipping_range(3,4);
 }


