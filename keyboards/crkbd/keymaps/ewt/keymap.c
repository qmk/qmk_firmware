/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum custom_layers {
    _QWERTY,
    _SYMBOL,
    _NAVIGATION,
    _FKEYS,
};


#define SYM MO(_SYMBOL)
#define NAV MO(_NAVIGATION)
#define MED MO(_FKEYS)

#define ECTRL LCTL_T(KC_ESC)
#define JCTRL RCTL_T(KC_J)
#define KALT LALT_T(KC_K)        
#define DASHMED LT(_FKEYS, KC_MINS)    
#define TMUX LCTL(KC_B)
#define KILL LALT(KC_F4)
#define CTL0 LCTL(KC_0)
#define CTL1 LCTL(KC_1)
#define CTL2 LCTL(KC_2)
#define CTL3 LCTL(KC_3)
#define CTL4 LCTL(KC_4)
#define CTL5 LCTL(KC_5)
#define CTL6 LCTL(KC_6)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      ECTRL,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  DASHMED,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_S,     KC_D,   KC_F,    KC_G,                         KC_H,   JCTRL,    KALT,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          SYM,    KC_SPC,  KC_BSPC,     KC_DEL,   KC_ENT, NAV
                                      //`--------------------------'  `--------------------------'

  ),

  [_SYMBOL] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      ECTRL,  KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                      KC_PEQL, KC_7,    KC_8,    KC_9,    KC_ASTR, KC_AMPR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,  KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                       KC_DOT,  KC_4,    KC_5,    KC_6,    KC_PLUS, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                      KC_0,    KC_1,    KC_2,    KC_3,    KC_BSLS, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX,  KC_SPC,  KC_BSPC,   KC_DEL,   KC_ENT, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAVIGATION] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      ECTRL,  XXXXXXX, KC_LCMD, KC_MS_U,  KC_F5, KC_WH_U,                       KC_PGUP, KC_HOME, KC_MINS, XXXXXXX, KC_END,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,  XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,                      KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, XXXXXXX, KC_MPLY,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, KC_PSCR, KC_COPY,  KC_PASTE, TMUX,                       KC_PGDN, XXXXXXX, KC_MPRV, KC_MNXT, XXXXXXX, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX,  KC_BTN1,  KC_BTN2,   KC_DEL,   KC_ENT, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_FKEYS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_F1,   KC_F2,     KC_F3,   KC_F4,   KC_F5,  KC_F6,                       KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT, KC_VOLU, XXXXXXX, KC_MRWD, XXXXXXX, KC_MNXT,                    XXXXXXX, CTL4,    CTL5,    CTL6,    XXXXXXX, KILL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_VOLD, KC_MUTE, DT_UP, DT_DOWN, DT_PRNT,                 CTL0,    CTL1,    CTL2,    CTL3,    XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX,  KC_SPC,  KC_BSPC,   KC_DEL,   KC_ENT, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};
