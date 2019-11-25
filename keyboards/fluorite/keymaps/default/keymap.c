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

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _CUSTOM1 4
#define _CUSTOM2 8
#define _ADJUST 16

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  CUSTOM1,
  CUSTOM2,
  ADJUST,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
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
  [_QWERTY] = LAYOUT_kc( /* Base */
         //,-------------------------------------------------------.  ,-------------------------------------------------------.
                F1,    F2,    F3,    F4,  PSCR,  PAST,  PSLS,    P0,     NLCK,  PSLS,  PAST,  BSPC,    F1,    F2,    F3,    F4,\
         //|------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------|
                F5,    F6,    F7,    F8,  PMNS,    P7,    P8,    P9,       P7,    P8,    P9,  PMNS,    F5,    F6,    F7,    F8,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
       LGUI,    F9,   F10,   F11,   F12,  PPLS,    P4,    P5,    P6,       P4,    P5,    P6,  PPLS,    F9,   F10,   F11,   F12,  RGUI,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          1,     2,     3,     4,     5,   ESC,    P1,    P2,    P3,       P1,    P2,    P3,   TAB,     6,     7,     8,     9,     0,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          Q,     W,     E,     R,     T,  BSPC,     Y,   INS,  PDOT,       P0,  PDOT,  PGUP,  HOME,     Y,     U,     I,     O,     P,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          A,     S,     D,     F,     G,   DEL,     N,    UP,  PENT,     PENT,    UP,  PGDN,   END,     H,     J,     K,     L,  MINS,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          Z,     X,     C,     V,     B,  LSFT,  LEFT,  DOWN, RIGHT,     LEFT,  DOWN, RIGHT,  RSFT,     N,     M,  COMM,   DOT,  SLSH,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
        GRV,   TAB,  LSFT,  LCTL, TTCM1,   SPC, LOWER,  LCTL,  LALT,     RALT,  RCTL, RAISE,   ENT,   ESC,   APP,  QUOT,   EQL,  BSPC \
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
  ),

  [_LOWER] = LAYOUT_kc( /* Base */
         //,-------------------------------------------------------.  ,-------------------------------------------------------.
                F1,    F2,    F3,    F4,  PSCR,  PAST,  PSLS,    P0,     NLCK,  PSLS,  PAST,  BSPC,    F1,    F2,    F3,    F4,\
         //|------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------|
                F5,    F6,    F7,    F8,  PMNS,    P7,    P8,    P9,       P7,    P8,    P9,  PMNS,    F5,    F6,    F7,    F8,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
       LGUI,    F9,   F10,   F11,   F12,  PPLS,    P4,    P5,    P6,       P4,    P5,    P6,  PPLS,    F9,   F10,   F11,   F12,  RGUI,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  LBRC,    P1,    P2,    P3,       P1,    P2,    P3,  RBRC,    F6,    F7,    F8,    F9,   F10,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  BSPC,     Y,   INS,  PDOT,       P0,  PDOT,  PGUP,  HOME,   F11,   F12, XXXXX, XXXXX,  RSJY,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
       PSLS,  PAST,  PMNS,  PPLS,  BSPC,   DEL,     N,    UP,  PENT,     PENT,    UP,  PGDN,   END,  BSPC, XXXXX, XXXXX, XXXXX,  SCLN,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
      LCTLZ, LCTLX, LCTLC, LCTLV,   DEL,  LSFT,  LEFT,  DOWN, RIGHT,     LEFT,  DOWN, RIGHT,  RSFT,   DEL, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
        GRV,   TAB,  LSFT,  LCTL,   ESC,   SPC, LOWER,  LCTL,  LALT,     RALT,  RCTL, RAISE,   ENT,   ESC,   APP,   ENT,   EQL,   DEL \
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
  ),

  [_RAISE] = LAYOUT_kc( /* Base */
         //,-------------------------------------------------------.  ,-------------------------------------------------------.
                F1,    F2,    F3,    F4,  PSCR,  PAST,  PSLS,    P0,     NLCK,  PSLS,  PAST,  BSPC,    F1,    F2,    F3,    F4,\
         //|------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------|
                F5,    F6,    F7,    F8,  PMNS,    P7,    P8,    P9,       P7,    P8,    P9,  PMNS,    F5,    F6,    F7,    F8,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
       LGUI,    F9,   F10,   F11,   F12,  PPLS,    P4,    P5,    P6,       P4,    P5,    P6,  PPLS,    F9,   F10,   F11,   F12,  RGUI,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
         F1,    F2,    F3,    F4,    F5,   ESC,    P1,    P2,    P3,       P1,    P2,    P3,   TAB, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  BSPC,     Y,   INS,  PDOT,       P0,  PDOT,  PGUP,  HOME, XXXXX,  HOME,    UP,   END,  RSJY,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,   DEL,     N,    UP,  PENT,     PENT,    UP,  PGDN,   END,  BSPC,  LEFT,  DOWN, RIGHT,  LBRC,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  LSFT,  LEFT,  DOWN, RIGHT,     LEFT,  DOWN, RIGHT,  RSFT,   DEL,  RSRO,  SCLN,  QUOT,    RO,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
        GRV,   TAB,  LSFT,  LCTL,   ESC,   SPC, LOWER,  LCTL,  LALT,     RALT,  RCTL, RAISE,   ENT,   ESC,   APP,   ENT,  BSLS,   DEL \
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
  ),

  [_CUSTOM1] = LAYOUT_kc( /* Base */
         //,-------------------------------------------------------.  ,-------------------------------------------------------.
                F1,    F2,    F3,    F4,  PSCR,  PPLS,  PMNS,    P0,     NLCK,  PSLS,  PAST,  BSPC,    F1,    F2,    F3,    F4,\
         //|------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------|
                F5,    F6,    F7,    F8,  PMNS,    P7,    P8,    P9,       P7,    P8,    P9,  PMNS,    F5,    F6,    F7,    F8,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
       LGUI,    F9,   F10,   F11,   F12,  PPLS,    P4,    P5,    P6,       P4,    P5,    P6,  PPLS,    F9,   F10,   F11,   F12,  RGUI,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          Y,     U,     I,     O,     P,   ESC,    P1,    P2,    P3,       P1,    P2,    P3,   TAB,     6,     7,     8,     9,     0,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          Q,     W,     E,     R,     T,  BSPC,    P0,   INS,  PDOT,       P0,  PDOT,  PGUP,  HOME,     Y,     U,     I,     O,     P,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          A,     S,     D,     F,     G,   DEL,     H,    UP,  PENT,     PENT,    UP,  PGDN,   END,     H,     J,     K,     L,  MINS,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          Z,     X,     C,     V,     B,   SPC,  LEFT,  DOWN, RIGHT,     LEFT,  DOWN, RIGHT,  RSFT,     N,     M,  COMM,   DOT,  SLSH,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          N,   TAB,  LSFT,  LCTL, TTCM2,  LALT, TTCM1,  LCTL, LCTLY,     RALT,  RCTL, TTCM1,   ENT,   ESC,   SPC,   ENT,   DEL,  BSPC \
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
  ),

  [_CUSTOM2] = LAYOUT_kc( /* Base */
         //,-------------------------------------------------------.  ,-------------------------------------------------------.
                F1,    F2,    F3,    F4,  PSCR,  PPLS,  PMNS,    P0,     NLCK,  PSLS,  PAST,  BSPC,    F1,    F2,    F3,    F4,\
         //|------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------|
                F5,    F6,    F7,    F8,  PMNS,    P7,    P8,    P9,       P7,    P8,    P9,  PMNS,    F5,    F6,    F7,    F8,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
       LGUI,    F9,   F10,   F11,   F12,  PPLS,    P4,    P5,    P6,       P4,    P5,    P6,  PPLS,    F9,   F10,   F11,   F12,  RGUI,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          Y,     M,     I,     L,     P,     H,    P1,    P2,    P3,       P1,    P2,    P3,   TAB,     6,     7,     8,     9,     0,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          Q,     W,     E,     R,     T,  RBRC,  COMM,  BSPC,  PDOT,       P0,  PDOT,  PGUP,  HOME,     Y,     U,     I,     O,     P,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          A,     S,     D,     F,     G,  BSLS,   DOT,    UP,  PENT,     PENT,    UP,  PGDN,   END,     H,     J,     K,     L,  MINS,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          Z,     X,     C,     V,     B,   SPC,  LEFT,  DOWN, RIGHT,     LEFT,  DOWN, RIGHT,  RSFT,     N,     M,  COMM,   DOT,  SLSH,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          N,   TAB,  LSFT,  LCTL,   ESC,  LALT, TTCM2, LCTLZ, LCTLY,     RALT,  RCTL, TTCM2,   ENT,   ESC,   SPC,   ENT,   DEL,  BSPC \
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
  ),

  [_ADJUST] = LAYOUT_kc( /* Base */
         //,-------------------------------------------------------.  ,-------------------------------------------------------.
                F1,    F2,    F3,    F4, XXXXX, XXXXX, XXXXX, XXXXX,    XXXXX, XXXXX, XXXXX, XXXXX,    F1,    F2,    F3,    F4,\
         //|------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------|
                F5,    F6,    F7,    F8, XXXXX, XXXXX, XXXXX, XXXXX,    XXXXX, XXXXX, XXXXX, XXXXX,    F5,    F6,    F7,    F8,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
      XXXXX,    F9,   F10,   F11,   F12, XXXXX, XXXXX, XXXXX, XXXXX,    XXXXX, XXXXX, XXXXX, XXXXX,    F9,   F10,   F11,   F12, XXXXX,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,    XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
          1,     2,     3,     4,     5,  BSPC, XXXXX, XXXXX, XXXXX,    XXXXX, XXXXX, XXXXX,  HOME,     6,     7,     8,     9,     0,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
      LSFCO,  RCBR,  RBRC,  ASTR,  BSPC,   DEL, XXXXX,    UP, XXXXX,    XXXXX,    UP, XXXXX,   END,  BSPC,  LPRN,  BSLS,  PIPE, LSFDO,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX,   DEL,  LSFT,  LEFT,  DOWN, RIGHT,     LEFT,  DOWN, RIGHT,  RSFT,   DEL, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
        GRV,   TAB,  LSFT,  LALT,   ESC,   SPC, LOWER,  LCTL,  LALT,     RALT,  RCTL, RAISE,   ENT,   ESC,   APP,   ENT, XXXXX, XXXXX \
  //|------+------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------+------|
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
    case ADJUST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        layer_on(_ADJUST);
        // SEND_STRING("QMK is the best thing ever!");
      } else {
        layer_off(_ADJUST);
        // when keycode .QMKBEST is released
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
