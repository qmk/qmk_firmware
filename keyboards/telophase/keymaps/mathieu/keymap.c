/* Copyright 2015-2017 Jack Humbert
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

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _GAME,
  _MACRO,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum macros {
  M_EADDR = SAFE_RANGE,
  M_RGRDS,
  M_GITPS
};


#define QWERTY TO(_QWERTY)
#define GAME TO(_GAME)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define MAKRO MO(_MACRO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_QWERTY] = KEYMAP(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    KC_LCTL, XXXXXXX, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   QWERTY,  XXXXXXX, GAME,    MAKRO
),

[_GAME] = KEYMAP(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_UP,   KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_LEFT, KC_DOWN, KC_RIGHT,KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    KC_LCTL, KC_LALT, XXXXXXX, KC_1,    KC_2,    KC_SPC,  KC_SPC,  RAISE,   QWERTY,  XXXXXXX, GAME,    MAKRO
),

[_MACRO] = KEYMAP(
    RESET,   _______, _______, M_EADDR, M_RGRDS, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, M_GITPS, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_LOWER] = KEYMAP(
    KC_GRV,  KC_P7,   KC_P8,   KC_P9,   KC_PLUS, KC_EXLM, KC_AT,   KC_HASH, KC_LPRN, KC_RPRN, _______, KC_DEL,
    _______, KC_P4,   KC_P5,   KC_P6,   KC_MINS, KC_DLR,  KC_PERC, KC_CIRC, KC_LCBR, KC_RCBR, _______, _______,
    _______, KC_P1,   KC_P2,   KC_P3,   KC_EQL,  KC_AMPR, KC_ASTR, KC_BSLS, KC_LBRC, KC_RBRC, _______, _______,
    _______, KC_P0,   KC_DOT,  KC_COMM, _______, KC_UNDS, KC_UNDS, _______, _______, _______, _______, _______
),  
  
[_RAISE] = KEYMAP(
    _______, _______, _______, _______, _______, _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, KC_DEL,
    _______, _______, _______, _______, _______, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_ADJUST] = KEYMAP(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______,  _______, _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};

void matrix_init_user() {
  return;
}

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /// TEXT MACROS
    case M_EADDR:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("your@email.here" SS_DOWN(X_LCTRL) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_UP(X_LCTRL) SS_TAP(X_LEFT));
      }
      break;
    case M_RGRDS:
      if (record->event.pressed) {
        SEND_STRING("Regards," SS_TAP(X_ENTER) "Mat.");
      }
      break;
    case M_GITPS:
      if (record->event.pressed) {
        SEND_STRING("git add ." SS_TAP(X_ENTER) "git commit -m 'I made some changes'" SS_TAP(X_ENTER) "git push");
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {
  return;
}