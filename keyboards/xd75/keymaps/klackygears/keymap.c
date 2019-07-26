/* Copyright 2017 Wunder
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

<<<<<<< HEAD
// Layer shorthand


// Defines the keycodes used by our macros in process_record_user
// enum custom_keycodes {
//   QMKBEST = SAFE_RANGE,
//   QMKURL
// };
=======
>>>>>>> master

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  [_MACBASE] = LAYOUT_wrapper( \
<<<<<<< HEAD
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  _______________DVORAK_L1___________________,    KC_LBRC, KC_BSLS, KC_RBRC, _______________DVORAK_R1___________________, KC_QUOT,
    KC_CAPS, _______________DVORAK_L2___________________,    KC_HOME, KC_DEL,  KC_PGUP, _______________DVORAK_R2___________________, KC_ENT,
    KC_LSFT, _______________MACDVK_L3___________________,    KC_END,  KC_UP,   KC_PGDN, _______________MACDVK_R3___________________, KC_RSFT,
    RGB_MOD, KC_LGUI, KC_LALT, LT(_FUNC,KC_ENT), MT(MOD_LSFT,KC_SPC), LT(_MNMB,KC_BSPC),  KC_LEFT, KC_DOWN, KC_RGHT, LT(_MNMB,KC_TAB), LT(_SYMB,KC_ENT), LT(_MDIA,KC_ENT), KC_RALT, KC_RGUI, KC_RCTL
=======
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, _______________DVORAK_L1___________________, LCTL(KC_LEFT), LCTL(KC_UP), LCTL(KC_RIGHT), _______________DVORAK_R1___________________, _______,
    _______, _______________DVORAK_L2___________________, KC_MUTE, KC_VOLD, KC_VOLU, _______________DVORAK_R2___________________, _______,
    KC_LSFT, _______________MACDVK_L3___________________, KC_PGUP, KC_UP,   KC_PGDN, _______________MACDVK_R3___________________, KC_RSFT,
    RGB_MOD, _______, _______, ________MAC_THUMB_L______, KC_LEFT, KC_DOWN, KC_RGHT, ________MAC_THUMB_R______, _______, _______, _______
>>>>>>> master
  ),


  [_WINBASE] = LAYOUT_wrapper( \
<<<<<<< HEAD
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NLCK, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_MSEL, _______________DVORAK_L1___________________, KC_P7,   KC_P8,   KC_P9,   _______________DVORAK_R1___________________, KC_PAUS,
    KC_MPRV, _______________DVORAK_L2___________________, KC_P4,   KC_P5,   KC_P6,   _______________DVORAK_R2___________________, _______,
    KC_VOLD, _______________WINDVK_L3___________________, KC_P1,   KC_P2,   KC_P3,   _______________WINDVK_R3___________________, _______,
    _______, _______, RGB_TOG, LT(_FUNC,KC_ENT), MT(MOD_LSFT,KC_SPC), LT(_NUMB,KC_BSPC), KC_P0,   _______, KC_PDOT, LT(_NUMB,KC_TAB), LT(_SYMB,KC_ENT), LT(_MDIA,KC_ENT), _______, _______, _______
=======
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, _______________DVORAK_L1___________________, LCTL(KC_TAB), LGUI(KC_TAB), LCTL(LSFT(KC_TAB)), _______________DVORAK_R1___________________, _______,
    _______, _______________DVORAK_L2___________________, KC_MUTE, KC_VOLD, KC_VOLU, _______________DVORAK_R2___________________, _______,
    _______, _______________WINDVK_L3___________________, KC_PGUP, KC_UP,   KC_PGDN, _______________WINDVK_R3___________________, _______,
    _______, _______, RGB_TOG, ________WIN_THUMB_L______, KC_LEFT, KC_DOWN, KC_RGHT, ________WIN_THUMB_R______, _______, _______, _______
>>>>>>> master
  ),


  [_QWERTY] = LAYOUT_wrapper( \
<<<<<<< HEAD
    KC_ESC,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_NLCK, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_TAB,    _________________QWERTY_L1_________________,  KC_P7,   KC_P8,   KC_P9,   _________________QWERTY_R1_________________, KC_PAUS,
    KC_CAPS,   _________________QWERTY_L2_________________,  KC_P4,   KC_P5,   KC_P6,   _________________QWERTY_R2_________________, _______,
    KC_LSHIFT, _________________QWERTY_L3_________________,  KC_P1,   KC_P2,   KC_P3,   _________________QWERTY_R3_________________, _______,
    KC_LGUI,   _______, RGB_TOG, MO(_MNMB), RGB_RMOD,KC_SPACE, KC_P0,   _______, KC_PDOT, KC_SPACE, KC_PENT, MO(_MNMB), _______, _______, _______
=======
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_MINS, KC_PLUS, KC_QUES,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_TAB,  _________________QWERTY_L1_________________,  LCTL(KC_LEFT), LCTL(KC_UP), LCTL(KC_RIGHT), _________________QWERTY_R1_________________, KC_BSPC,
    KC_CAPS, _________________QWERTY_L2_________________,  KC_MUTE, KC_VOLD, KC_VOLU,   _________________QWERTY_R2_________________, KC_ENT,
    KC_LSFT, _________________QWERTY_L3_________________,  KC_PGUP, KC_UP,   KC_PGDN,   _________________QWERTY_R3_________________, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LGUI, MO(_MNMB), MO(_SYMB),  KC_SPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC, MO(_SYMB), MO(_MNMB), KC_RGUI, MO(_MDIA), MO(_FUNC)
>>>>>>> master
  ),


  [_SYMB] = LAYOUT_wrapper( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NLCK, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
<<<<<<< HEAD
    KC_MSEL, _________________PUNC_L1_ALT_______________, KC_P7,   KC_P8,   KC_P9,   _________________PUNC_R1___________________, KC_PAUS,
    KC_MPRV, _________________PUNC_L3___________________, KC_P4,   KC_P5,   KC_P6,   _________________PUNC_R2___________________, _______,
    KC_VOLD, _________________PUNC_L3_ALT_______________, KC_P1,   KC_P2,   KC_P3,   _________________PUNC_R3___________________, _______,
    _______, _______, RGB_TOG, MO(_MNMB), RGB_RMOD,RGB_MOD, KC_P0,   _______, KC_PDOT, KC_PENT, KC_PENT, MO(_MNMB), _______, _______, _______
=======
    KC_MSEL, _________________PUNC_L1_ALT_______________, KC_P7,   KC_P8,   KC_P9,   _________________PUNC_R1___________________, _______,
    KC_MPRV, _________________PUNC_L3___________________, KC_P4,   KC_P5,   KC_P6,   _________________PUNC_R2___________________, _______,
    KC_VOLD, _________________PUNC_L3_ALT_______________, KC_P1,   KC_P2,   KC_P3,   _________________PUNC_R3___________________, _______,
    _________________KC_BLANK__________________, _________________KC_BLANK__________________, _________________KC_BLANK__________________
>>>>>>> master
  ),


  [_FUNC] = LAYOUT_wrapper( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_NLCK, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,     KC_F12,
<<<<<<< HEAD
    KC_MSEL, _____________FUNC_L1_______________________,    KC_P7,   KC_P8,   KC_P9,   KC_WINBASE, _____________FUNC_1_______________, KC_PAUS,
    KC_MPRV, ________MAC_MISSION_CTRL__________, LGUI(KC_L), KC_P4,   KC_P5,   KC_P6,   KC_MACBASE, _____________FUNC_2_______________, _______,
    KC_VOLD, _____________FUNC_L3_______________________,    KC_P1,   KC_P2,   KC_P3,   KC_GRV,     _____________FUNC_3_______________, _______,
    _______, _______, RGB_TOG, MO(_MNMB), RGB_RMOD,RGB_MOD,    KC_P0,   _______, KC_PDOT, KC_PENT, KC_PENT, MO(_MNMB), _______, _______,    _______
=======
    _______, _____________FUNC_L1_______________________, _______, _______, _______, _______, _____________FUNC_1_______________, _______,
    _______, ________MAC_MISSION_CTRL__________, LGUI(KC_L), _______, _______, _______, _______, _____________FUNC_2_______________, _______,
    _______, _____________FUNC_L3_______________________, _______, _______, _______, KC_GRV,  _____________FUNC_3_______________, _______,
    _________________KC_BLANK__________________, _________________KC_BLANK__________________, _________________KC_BLANK__________________
>>>>>>> master
  ),


  [_MNMB] = LAYOUT_wrapper( \
<<<<<<< HEAD
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NLCK, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_MSEL, _________________MACNAV_L1_________________, KC_P7,   KC_P8,   KC_P9,   _________________NUMB_R1___________________, KC_PAUS,
    KC_MPRV, _________________MACNAV_L2_________________, KC_P4,   KC_P5,   KC_P6,   _________________NUMB_R2___________________, _______,
    KC_VOLD, _________________MACNAV_L3_________________, KC_P1,   KC_P2,   KC_P3,   _________________NUMB_R3_MAC_______________, _______,
    _______, _______, RGB_TOG, MO(_MNMB), RGB_RMOD,RGB_MOD, KC_P0,   _______, KC_PDOT, KC_PENT, KC_PENT, MO(_MNMB), _______, _______, _______
=======
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_MINS, KC_PLUS, KC_QUES,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_MSEL, _________________MACNAV_L1_________________, _______, _______, _______, _________________NUMB_R1___________________, KC_PAUS,
    KC_MPRV, _________________MACNAV_L2_________________, _______, _______, _______, _________________NUMB_R2___________________, _______,
    KC_VOLD, _________________MACNAV_L3_________________, _______, _______, _______, _________________NUMB_R3_MAC_______________, _______,
    _________________KC_BLANK__________________, _________________KC_BLANK__________________, _________________KC_BLANK__________________
>>>>>>> master
  ),


  [_NUMB] = LAYOUT_wrapper( \
<<<<<<< HEAD
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NLCK, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_MSEL, _________________WINNAV_L1_________________, KC_P7,   KC_P8,   KC_P9,   _________________NUMB_R1___________________, KC_PAUS,
    KC_MPRV, _________________WINNAV_L2_________________, KC_P4,   KC_P5,   KC_P6,   _________________NUMB_R2___________________, _______,
    KC_VOLD, _________________WINNAV_L3_________________, KC_P1,   KC_P2,   KC_P3,   _________________NUMB_R3_WIN_______________, _______,
    _______, _______, RGB_TOG, MO(_MNMB), RGB_RMOD,RGB_MOD, KC_P0,   _______, KC_PDOT, KC_PENT, KC_PENT, MO(_MNMB), _______, _______, _______
=======
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_MINS, KC_PLUS, KC_QUES,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_MSEL, _________________WINNAV_L1_________________, _______, _______, _______, _________________NUMB_R1___________________, KC_PAUS,
    KC_MPRV, _________________WINNAV_L2_________________, _______, _______, _______, _________________NUMB_R2___________________, _______,
    KC_VOLD, _________________WINNAV_L3_________________, _______, _______, _______, _________________NUMB_R3_WIN_______________, _______,
    _________________KC_BLANK__________________, _________________KC_BLANK__________________, _________________KC_BLANK__________________
>>>>>>> master
  ),


  [_MDIA] = LAYOUT_wrapper( \
<<<<<<< HEAD
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NLCK, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_MSEL, _________________LYOUT_____________________, KC_P7,   KC_P8,   KC_P9,   _________________RGB_1_____________________, _______,
    KC_MPRV, _________________KC_BLANK__________________, KC_P4,   KC_P5,   KC_P6,   _________________RGB_2_____________________, _______,
    KC_VOLD, _________________KC_BLANK__________________, KC_P1,   KC_P2,   KC_P3,   _________________MEDIA_____________________, _______,
    _______, _______, RGB_TOG, MO(_MNMB), RGB_RMOD,RGB_MOD, KC_P0,   _______, KC_PDOT, KC_PENT, KC_PENT, MO(_MNMB), _______, _______, _______
=======
    _________________KC_BLANK__________________, _________________KC_BLANK__________________, _________________KC_BLANK__________________,
    KC_MSEL, _________________LYOUT_____________________, _______, _______, _______, _________________RGB_1_____________________, _______,
    KC_MPRV, _________________KC_BLANK__________________, _______, _______, _______, _________________RGB_2_____________________, _______,
    KC_VOLD, _________________KC_BLANK__________________, _______, _______, _______, _________________MEDIA_____________________, _______,
    _________________KC_BLANK__________________, _________________KC_BLANK__________________, _________________KC_BLANK__________________
>>>>>>> master
  )

};

<<<<<<< HEAD
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case QMKBEST:
//       if (record->event.pressed) {
//         // when keycode QMKBEST is pressed
//         SEND_STRING("QMK is the best thing ever!");
//       } else {
//         // when keycode QMKBEST is released
//       }
//       break;
//     case QMKURL:
//       if (record->event.pressed) {
//         // when keycode QMKURL is pressed
//         SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
//       } else {
//         // when keycode QMKURL is released
//       }
//       break;
//   }
//   return true;
// }
=======


>>>>>>> master

// void matrix_init_user(void) {

// }

// void matrix_scan_user(void) {

// }

// void led_set_user(uint8_t usb_led) {

// }
<<<<<<< HEAD
=======

#ifdef RGBLIGHT_EFFECT_SNAKE
__attribute__ ((weak))
const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {35, 25, 15};
#endif

#ifdef RGBLIGHT_EFFECT_KNIGHT
__attribute__ ((weak))
const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {35, 29, 17};
#endif
>>>>>>> master
