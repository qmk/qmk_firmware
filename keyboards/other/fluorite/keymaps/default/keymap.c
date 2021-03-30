/* Copyright 2019 Mafuyu Ihotsuno
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

enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _CUSTOM1,
    _CUSTOM2,
    _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

#define KC_TTCM1 TT(_CUSTOM1)
#define KC_TTCM2 TT(_CUSTOM2)
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)
#define KC_RSHM RSFT(KC_HOME)
#define KC_RSEN RSFT(KC_END)
#define KC_RSJY RSFT(KC_JYEN)
#define KC_RSRO RSFT(KC_RO)
#define KC_LSTAB LSFT(KC_TAB)
#define KC_LSFCO LSFT(KC_COMM)
#define KC_LSFDO LSFT(KC_DOT)
#define KC_LCTLZ LCTL(KC_Z)
#define KC_LCTLX LCTL(KC_X)
#define KC_LCTLC LCTL(KC_C)
#define KC_LCTLV LCTL(KC_V)
#define KC_LCTLY LCTL(KC_Y)
#define KC_LALSP LALT(KC_SPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( /* Base */
            //,-------------------------------------------------------------------------------.  ,-------------------------------------------------------------------------------.
                   KC_F1,    KC_F2,    KC_F3,    KC_F4,  KC_PSCR,  KC_PAST,  KC_PSLS,    KC_P0,     KC_NLCK,  KC_PSLS,  KC_PAST,  KC_BSPC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,\
            //|---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------|
                   KC_F5,    KC_F6,    KC_F7,    KC_F8,  KC_PMNS,    KC_P7,    KC_P8,    KC_P9,       KC_P7,    KC_P8,    KC_P9,  KC_PMNS,    KC_F5,    KC_F6,    KC_F7,    KC_F8,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_LGUI,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_PPLS,    KC_P4,    KC_P5,    KC_P6,       KC_P4,    KC_P5,    KC_P6,  KC_PPLS,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_RGUI,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_1,     KC_2,     KC_3,     KC_4,     KC_5,   KC_ESC,    KC_P1,    KC_P2,    KC_P3,       KC_P1,    KC_P2,    KC_P3,   KC_TAB,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,  KC_BSPC,     KC_Y,   KC_INS,  KC_PDOT,       KC_P0,  KC_PDOT,  KC_PGUP,  KC_HOME,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_A,     KC_S,     KC_D,     KC_F,     KC_G,   KC_DEL,     KC_N,    KC_UP,  KC_PENT,     KC_PENT,    KC_UP,  KC_PGDN,   KC_END,     KC_H,     KC_J,     KC_K,     KC_L,  KC_MINS,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,  KC_LSFT,  KC_LEFT,  KC_DOWN, KC_RIGHT,     KC_LEFT,  KC_DOWN, KC_RIGHT,  KC_RSFT,     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_GRV,   KC_TAB,  KC_LSFT,  KC_LCTL, KC_TTCM1,   KC_SPC,    LOWER,  KC_LCTL,  KC_LALT,     KC_RALT,  KC_RCTL,    RAISE,   KC_ENT,   KC_ESC,   KC_APP,  KC_QUOT,   KC_EQL,  KC_BSPC \
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
  ),

  [_LOWER] = LAYOUT( /* Base */
            //,-------------------------------------------------------------------------------.  ,-------------------------------------------------------------------------------.
                   KC_F1,    KC_F2,    KC_F3,    KC_F4,  KC_PSCR,  KC_PAST,  KC_PSLS,    KC_P0,     KC_NLCK,  KC_PSLS,  KC_PAST,  KC_BSPC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,\
            //|---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------|
                   KC_F5,    KC_F6,    KC_F7,    KC_F8,  KC_PMNS,    KC_P7,    KC_P8,    KC_P9,       KC_P7,    KC_P8,    KC_P9,  KC_PMNS,    KC_F5,    KC_F6,    KC_F7,    KC_F8,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_LGUI,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_PPLS,    KC_P4,    KC_P5,    KC_P6,       KC_P4,    KC_P5,    KC_P6,  KC_PPLS,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_RGUI,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LBRC,    KC_P1,    KC_P2,    KC_P3,       KC_P1,    KC_P2,    KC_P3,  KC_RBRC,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_BSPC,     KC_Y,   KC_INS,  KC_PDOT,       KC_P0,  KC_PDOT,  KC_PGUP,  KC_HOME,   KC_F11,   KC_F12,  XXXXXXX,  XXXXXXX,  KC_RSJY,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_PSLS,  KC_PAST,  KC_PMNS,  KC_PPLS,  KC_BSPC,   KC_DEL,     KC_N,    KC_UP,  KC_PENT,     KC_PENT,   KC_UP,  KC_PGDN,   KC_END,   KC_BSPC,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_SCLN,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
      KC_LCTLZ, KC_LCTLX, KC_LCTLC, KC_LCTLV,   KC_DEL,  KC_LSFT,  KC_LEFT,  KC_DOWN, KC_RIGHT,     KC_LEFT,  KC_DOWN, KC_RIGHT,  KC_RSFT,   KC_DEL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_GRV,   KC_TAB,  KC_LSFT,  KC_LCTL,   KC_ESC,   KC_SPC,    LOWER,  KC_LCTL,  KC_LALT,     KC_RALT,  KC_RCTL,    RAISE,   KC_ENT,   KC_ESC,   KC_APP,   KC_ENT,   KC_EQL,   KC_DEL \
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
  ),

  [_RAISE] = LAYOUT( /* Base */
            //,-------------------------------------------------------------------------------.  ,-------------------------------------------------------------------------------.
                   KC_F1,    KC_F2,    KC_F3,    KC_F4,  KC_PSCR,  KC_PAST,  KC_PSLS,    KC_P0,     KC_NLCK,  KC_PSLS,  KC_PAST,  KC_BSPC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,\
            //|---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------|
                   KC_F5,    KC_F6,    KC_F7,    KC_F8,  KC_PMNS,    KC_P7,    KC_P8,    KC_P9,       KC_P7,    KC_P8,    KC_P9,  KC_PMNS,    KC_F5,    KC_F6,    KC_F7,    KC_F8,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_LGUI,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_PPLS,    KC_P4,    KC_P5,    KC_P6,       KC_P4,    KC_P5,    KC_P6,  KC_PPLS,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_RGUI,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
         KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,   KC_ESC,    KC_P1,    KC_P2,    KC_P3,       KC_P1,    KC_P2,    KC_P3,   KC_TAB,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_BSPC,     KC_Y,   KC_INS,  KC_PDOT,       KC_P0,  KC_PDOT,  KC_PGUP,  KC_HOME,  XXXXXXX,  KC_HOME,    KC_UP,   KC_END,  KC_RSJY,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   KC_DEL,     KC_N,    KC_UP,  KC_PENT,     KC_PENT,    KC_UP,  KC_PGDN,   KC_END,  KC_BSPC,  KC_LEFT,  KC_DOWN, KC_RIGHT,  KC_LBRC,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LSFT,  KC_LEFT,  KC_DOWN, KC_RIGHT,     KC_LEFT,  KC_DOWN, KC_RIGHT,  KC_RSFT,   KC_DEL,  KC_RSRO,  KC_SCLN,  KC_QUOT,    KC_RO,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_GRV,   KC_TAB,  KC_LSFT,  KC_LCTL,   KC_ESC,   KC_SPC,    LOWER,  KC_LCTL,  KC_LALT,     KC_RALT,  KC_RCTL,    RAISE,   KC_ENT,   KC_ESC,   KC_APP,   KC_ENT,  KC_BSLS,   KC_DEL \
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
  ),

  [_CUSTOM1] = LAYOUT( /* Base */
            //,-------------------------------------------------------------------------------.  ,-------------------------------------------------------------------------------.
                   KC_F1,    KC_F2,    KC_F3,    KC_F4,  KC_PSCR,  KC_PPLS,  KC_PMNS,    KC_P0,     KC_NLCK,  KC_PSLS,  KC_PAST,  KC_BSPC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,\
            //|---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------|
                   KC_F5,    KC_F6,    KC_F7,    KC_F8,  KC_PMNS,    KC_P7,    KC_P8,    KC_P9,       KC_P7,    KC_P8,    KC_P9,  KC_PMNS,    KC_F5,    KC_F6,    KC_F7,    KC_F8,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_LGUI,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_PPLS,    KC_P4,    KC_P5,    KC_P6,       KC_P4,    KC_P5,    KC_P6,  KC_PPLS,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_RGUI,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,   KC_ESC,    KC_P1,    KC_P2,    KC_P3,       KC_P1,    KC_P2,    KC_P3,   KC_TAB,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,  KC_BSPC,    KC_P0,   KC_INS,  KC_PDOT,       KC_P0,  KC_PDOT,  KC_PGUP,  KC_HOME,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_A,     KC_S,     KC_D,     KC_F,     KC_G,   KC_DEL,     KC_H,    KC_UP,  KC_PENT,     KC_PENT,    KC_UP,  KC_PGDN,   KC_END,     KC_H,     KC_J,     KC_K,     KC_L,  KC_MINS,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,   KC_SPC,  KC_LEFT,  KC_DOWN, KC_RIGHT,     KC_LEFT,  KC_DOWN, KC_RIGHT,  KC_RSFT,     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_N,   KC_TAB,  KC_LSFT,  KC_LCTL, KC_TTCM2,  KC_LALT, KC_TTCM1,  KC_LCTL, KC_LCTLY,     KC_RALT,  KC_RCTL, KC_TTCM1,   KC_ENT,   KC_ESC,   KC_SPC,   KC_ENT,   KC_DEL,  KC_BSPC \
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
  ),

  [_CUSTOM2] = LAYOUT( /* Base */
            //,-------------------------------------------------------------------------------.  ,-------------------------------------------------------------------------------.
                   KC_F1,    KC_F2,    KC_F3,    KC_F4,  KC_PSCR,  KC_PPLS,  KC_PMNS,    KC_P0,     KC_NLCK,  KC_PSLS,  KC_PAST,  KC_BSPC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,\
            //|---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------|
                   KC_F5,    KC_F6,    KC_F7,    KC_F8,  KC_PMNS,    KC_P7,    KC_P8,    KC_P9,       KC_P7,    KC_P8,    KC_P9,  KC_PMNS,    KC_F5,    KC_F6,    KC_F7,    KC_F8,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_LGUI,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_PPLS,    KC_P4,    KC_P5,    KC_P6,       KC_P4,    KC_P5,    KC_P6,  KC_PPLS,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_RGUI,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_Y,     KC_M,     KC_I,     KC_L,     KC_P,     KC_H,    KC_P1,    KC_P2,    KC_P3,       KC_P1,    KC_P2,    KC_P3,   KC_TAB,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,  KC_RBRC,  KC_COMM,  KC_BSPC,  KC_PDOT,       KC_P0,  KC_PDOT,  KC_PGUP,  KC_HOME,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_A,     KC_S,     KC_D,     KC_F,     KC_G,  KC_BSLS,   KC_DOT,    KC_UP,  KC_PENT,     KC_PENT,    KC_UP,  KC_PGDN,   KC_END,     KC_H,     KC_J,     KC_K,     KC_L,  KC_MINS,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,   KC_SPC,  KC_LEFT,  KC_DOWN, KC_RIGHT,     KC_LEFT,  KC_DOWN, KC_RIGHT,  KC_RSFT,     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_N,   KC_TAB,  KC_LSFT,  KC_LCTL,   KC_ESC,  KC_LALT, KC_TTCM2, KC_LCTLZ, KC_LCTLY,     KC_RALT,  KC_RCTL, KC_TTCM2,   KC_ENT,   KC_ESC,   KC_SPC,   KC_ENT,   KC_DEL,  KC_BSPC \
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
  ),

  [_ADJUST] = LAYOUT( /* Base */
            //,-------------------------------------------------------------------------------.  ,-------------------------------------------------------------------------------.
                   KC_F1,    KC_F2,    KC_F3,    KC_F4,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    KC_F1,    KC_F2,    KC_F3,    KC_F4,\
            //|---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------|
                   KC_F5,    KC_F6,    KC_F7,    KC_F8,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    KC_F5,    KC_F6,    KC_F7,    KC_F8,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
       XXXXXXX,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  XXXXXXX,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_1,     KC_2,     KC_3,     KC_4,     KC_5,  KC_BSPC,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_HOME,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
      KC_LSFCO,  KC_RCBR,  KC_RBRC,  KC_ASTR,  KC_BSPC,   KC_DEL,  XXXXXXX,    KC_UP,  XXXXXXX,     XXXXXXX,    KC_UP,  XXXXXXX,   KC_END,  KC_BSPC,  KC_LPRN,  KC_BSLS,  KC_PIPE, KC_LSFDO,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   KC_DEL,  KC_LSFT,  KC_LEFT,  KC_DOWN, KC_RIGHT,     KC_LEFT,  KC_DOWN, KC_RIGHT,  KC_RSFT,   KC_DEL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_GRV,   KC_TAB,  KC_LSFT,  KC_LALT,   KC_ESC,   KC_SPC,    LOWER,  KC_LCTL,  KC_LALT,     KC_RALT,  KC_RCTL,    RAISE,   KC_ENT,   KC_ESC,   KC_APP,   KC_ENT,  XXXXXXX,  XXXXXXX \
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------+---------+---------|
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        // SEND_STRING("QMK is the best thing ever!");
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        // when keycode QMKBEST is released
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        // SEND_STRING("QMK is the best thing ever!");
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        // when keycode QMKBEST is released
      }
      return false;
      break;
  }
  return true;
}
