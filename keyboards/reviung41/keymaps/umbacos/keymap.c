/* Copyright 2020 gtips
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

enum layer_names {
    _BASE,
    _SHIFT,
    _NUMBER,
    _SYMBOL,
    _ACCENT,
    _ADJUST,
};

enum custom_keycodes {
    BRACKETS = SAFE_RANGE,
    PARENTES,
    CURLYBRK
};

#define NUMBER MO(_NUMBER)
#define SYMBOL MO(_SYMBOL)
#define ADJUST MO(_ADJUST)

#define KC_SF(x) MT(MOD_LSFT, x)
#define SHIFT(x) LT(_SHIFT, x)
#define SPACCENT LT(_ACCENT, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung41(
    KC_SF(KC_ESC),  KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    KC_SF(KC_TAB),  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     IT_QUOT,  KC_SFTENT,
    SHIFT(KC_DEL),  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     IT_COMM,  SHIFT(IT_DOT),   IT_SCLN,  SHIFT(KC_PSLS),
                                                KC_LCTL,   KC_LGUI,   SPACCENT,   NUMBER,  SYMBOL
  ),

  [_SHIFT] = LAYOUT_reviung41(
    S(KC_ESC),  S(KC_Q),    S(KC_W), S(KC_E), S(KC_R), S(KC_T),             S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), S(KC_BSPC),
    S(KC_TAB),  S(KC_A),    S(KC_S), S(KC_D), S(KC_F), S(KC_G),             S(KC_H), S(KC_J), S(KC_K), S(KC_L), IT_DQUO, S(KC_ENT),
    PARENTES,   S(KC_Z),    S(KC_X), S(KC_C), S(KC_V), S(KC_B),             S(KC_N), S(KC_M), IT_BSLS, IT_PIPE, S(IT_COLN), IT_QUES,
                                        S(KC_LCTL), S(KC_LGUI),  SPACCENT,  SYMBOL,  S(KC_RALT)
  ),

  [_NUMBER] = LAYOUT_reviung41(
    IT_LESS,               KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    IT_CIRC,
    MT(MOD_LSFT, KC_TAB),  KC_PPLS, KC_PMNS, KC_PSLS, KC_PAST, XXXXXXX,             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UP, KC_SFTENT,
    LT(_SYMBOL, BRACKETS), IT_LBRC, IT_RBRC, IT_EQL,  KC_DOT,  XXXXXXX,             XXXXXXX, XXXXXXX, IT_COMM, KC_LEFT, KC_DOWN, LT(_SYMBOL, KC_RIGHT),
                                                    KC_LCTL,   KC_LGUI,  SPACCENT,  _______,  KC_RALT
  ),

  [_SYMBOL] = LAYOUT_reviung41(
    IT_MORE,                IT_EXLM, IT_AT,   IT_HASH, IT_DLR,  IT_PERC,             IT_CRC,   IT_AMPR,  IT_ASTR, IT_LPRN, IT_RPRN, IT_PLUS,
    S(KC_TAB),              IT_EQL,  IT_UNDS, KC_PSLS, KC_PAST, XXXXXXX,             XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, KC_UP, KC_SFTENT,
    MT(MOD_LSFT, CURLYBRK), IT_LCBR, IT_RCBR, _______, IT_RABK, IT_LABK,             IT_BSLS,  IT_PIPE, IT_UNDS, KC_LEFT, KC_DOWN, LT(_SYMBOL, KC_RIGHT),
                                                     KC_LCTL,   KC_RGUI,  SPACCENT,  KC_RALT,  _______
  ),

  [_ACCENT] = LAYOUT_reviung41(
    _______, IT_EURO, IT_AT,   IT_EGRV, _______, _______,              _______, IT_UGRV, IT_IGRV, IT_OGRV, _______, _______,
    _______, IT_AGRV, IT_SECT, _______, _______, IT_DEG,               _______, _______, _______, _______, _______, _______,
    KC_LSFT, IT_LPRN, IT_RPRN, IT_CCED, _______, _______,              _______, _______, IT_SCLN, IT_COLN, _______, KC_RSFT,
                                        KC_LCTL, KC_RGUI,   _______,  _ADJUST,    KC_RALT
  ),

  [_ADJUST] = LAYOUT_reviung41(
    RGB_VAI,  RGB_SAI,  RGB_HUI,  RGB_MOD,  XXXXXXX,  RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_VAD,  RGB_SAD,  RGB_HUD,  RGB_RMOD, XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,              KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
                                            _______,   _______,  RGB_MOD,  _______,  _______
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case PARENTES:
          if (record->event.pressed)
              SEND_STRING("*("SS_TAP(X_LEFT));
          break;
      case BRACKETS:
          if (record->event.pressed)
              SEND_STRING("è+"SS_TAP(X_LEFT));
          break;
      case CURLYBRK:
      if (record->event.pressed)
          SEND_STRING(SS_DOWN(X_LSHIFT)"è+"SS_UP(X_LSHIFT)SS_TAP(X_LEFT));
      break;
    }
    return true;
}
