/* Copyright 2020 Reid Sox-Harris
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
    _GAME,
    _UPPER,
    _LOWER,
    _UTILS
};

enum custom_keycodes {
  TMUX_WN = SAFE_RANGE,
  TMUX_WL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TMUX_WN:                       // Switches to next window in tmux
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("a") "n"); // Requires a leader of ctrl-a
      }
      break;

    case TMUX_WL:                       // Switches to last window in tmux
      if (record->event.pressed) {
          SEND_STRING(SS_LCTL("a") "l");
      }
      break;

  }
  return true;
};

#define UPPER       MO(_UPPER)
#define LOWER       MO(_LOWER)
#define GAME        TG(_GAME)
#define UTILS       MO(_UTILS)

#define WM_R        LCTL(KC_RGHT)       // Moves the MacOS WM to the right
#define WM_L        LCTL(KC_LEFT)       // ...and to the left
#define WM_MC       LCTL(KC_UP)         // Enters MacOS Mission Control
#define WEB_R       LGUI(KC_RCBR)       // Change tabs to the right on Firefox, Chrome
#define WEB_L       LGUI(KC_LCBR)       // ...and to the left
#define TMUX_U      RALT(KC_UP)         // tmux navigation, requires tmux.conf change
#define TMUX_D      RALT(KC_DOWN)
#define TMUX_R      RALT(KC_RGHT)
#define TMUX_L      RALT(KC_LEFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_GRV ,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_MINS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,  KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_LCTL,          KC_NO,    KC_N,    KC_M,  KC_COMM,  KC_DOT, KC_SLSH, KC_BSPC,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_LGUI, UPPER,   KC_ENT,                    KC_SPC,  LOWER,   KC_RALT
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
  [_GAME] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, KC_SPC,                     KC_ENT, _______, _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
  [_UPPER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                           KC_CIRC , KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  WEB_L,   WEB_R,   WM_MC,    WM_L,    WM_R,                             KC_LEFT,  KC_DOWN, KC_UP,  KC_RGHT, KC_PGUP, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  KC_NO,  KC_LABK, KC_LBRC, KC_LPRN, KC_LCBR, _______,          _______, KC_RCBR, KC_RPRN, KC_RBRC, KC_RABK, KC_PGDN,_______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______,  UPPER,  _______,                   _______,  UTILS,  _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_CAPS,  KC_F1,    KC_F2,  KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                           KC_CIRC , KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, TMUX_WL,  TMUX_WN,  KC_NO,   KC_NO,   KC_NO,                             TMUX_L,  TMUX_D,  TMUX_U,  TMUX_R,  KC_NO,  KC_PIPE,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  KC_NO,  _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,  KC_NO,   KC_DEL,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______,  UTILS,  _______,                   _______,  LOWER,  _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
  [_UTILS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_CAPS,  KC_F1,    KC_F2,  KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CAPS,  KC_F1,    KC_F2,  KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,                            KC_NO,   KC_INS,  KC_HOME, KC_PGUP, KC_NO,   GAME,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,  RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,_______,          _______,  KC_SLEP, KC_DEL,  KC_END,  KC_PGDN, KC_NO,   KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______,  KC_NO,  _______,                   _______, _______, _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};
