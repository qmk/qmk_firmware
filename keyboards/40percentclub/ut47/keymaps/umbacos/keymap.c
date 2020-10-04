/* Copyright 2018 Carlos Filoteo
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
#include "keymap_italian.h"

#ifdef LED_ENABLE
  #include "protocol/serial.h"
#endif

#define MT_RSFT_ENT MT(MOD_RSFT, KC_ENT)
#define MT_RSFT_TAB MT(MOD_RSFT, KC_TAB)

enum custom_keycodes {
    LED_TOG = SAFE_RANGE,
    LED_CHG
};
enum layers {
  _QWERTY,
  _SHIFT,
  _NUMBER,
  _SYMBOL,
  _ACCENT,
  _SERVICE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
  KC_GESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    LT(_ACCENT, KC_BSPC),
  MT_RSFT_TAB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    IT_APOS, MT_RSFT_ENT,
  LT(_SHIFT, KC_DEL), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,  KC_M,    KC_COMM, KC_DOT, KC_UP, LT(_SHIFT, KC_PSLS),
  KC_LCTL, KC_LALT, MO(_SERVICE),  KC_LGUI, KC_LGUI, LT(_ACCENT, KC_SPC), LT(_NUMBER, KC_SPC),  LT(_SHIFT,IT_SCLN), KC_LEFT, KC_DOWN,   KC_RGHT
),

[_SHIFT] = LAYOUT(
    S(KC_ESC),  S(KC_Q),    S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), KC_DEL,  \
    S(KC_TAB),  S(KC_A),    S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), IT_DQOT, S(KC_ENT), \
    IT_QST,    S(KC_Z),    S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), IT_BKSL,  IT_PIPE, S(KC_UP), IT_QST,  \
    S(KC_LCTL), S(KC_LALT), MO(_SERVICE), S(KC_LGUI), MO(_ACCENT), S(KC_SPC), MO(_NUMBER),  IT_COLN, S(KC_LEFT), S(KC_DOWN), S(KC_RGHT)  \
),

[_NUMBER] = LAYOUT(
   IT_DEGR,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
   _______, KC_PPLS, KC_PMNS, KC_PSLS, KC_PAST, XXXXXXX, IT_PLUS, IT_MINS, IT_EQL,  IT_LBRC, IT_RBRC, IT_LESS,
   LT(_SYMBOL, KC_DEL), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_DOT, KC_VOLU, LT(_SYMBOL, KC_DEL),
   _______, _______, _______, _______, KC_CAPS,     _______,      _______, _______, KC_MUTE, KC_VOLD, KC_MUTE
 ),

 [_SYMBOL] = LAYOUT(
     KC_TILDE, IT_EXLM, IT_AT,IT_SHRP, IT_DLR,  IT_PERC, IT_CRC,  IT_AMPR, IT_ASTR, IT_LPRN, IT_RPRN, KC_BSPC,
     S(KC_TAB), KC_PPLS, IT_UNDS, KC_PSLS, KC_PAST,XXXXXXX, IT_MORE, IT_LESS,  IT_LCBR, IT_LCBR, IT_RCBR, MT_RSFT_ENT,
     IT_DQOT,    S(KC_Z),    S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), IT_BKSL,  IT_PIPE, S(KC_UP), IT_QST,
     S(KC_LCTL), S(KC_LALT), MO(_SERVICE), S(KC_LGUI), LT(_ACCENT, KC_DEL), LT(_NUMBER, KC_SPC), _______,_______,S(KC_LEFT), S(KC_DOWN), S(KC_RGHT)
 ),

[_ACCENT] = LAYOUT(
  _______,  IT_EURO, IT_AT,  IT_EACC, _______, _______, _______, IT_UACC, IT_IACC, IT_OACC, _______, _______,
  _______, IT_AACC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_LSFT, _______,   _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU,  KC_RSFT,
  _______, _______, _______, _______, _______,     _______,      KC_CAPS, _______, _______, KC_VOLD, KC_MUTE
),

[_SERVICE] = LAYOUT(
  RESET,  KC_1,    KC_2,    KC_3, _______, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______,
  _______, KC_4,    KC_5,    KC_6, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
  _______, KC_7,    KC_8,    KC_9, KC_0, _______, _______, _______, _______, _______, KC_VOLU, KC_RSFT,
  _______, _______, _______, _______, _______,     _______,      _______, _______, _______, KC_VOLD, KC_MUTE
),
};

//LED keymap functions
 #ifdef LED_ENABLE
void led_chmode(void) {
  serial_send(101);
}

void led_toggle(void) {
  serial_send(100);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case LED_TOG:
        #ifdef LED_ENABLE
        led_toggle();
        #endif
        return false;
      case LED_CHG:
        #ifdef LED_ENABLE
        led_chmode();
        #endif
        return false;
    }
  }
  return true;
};
#endif
