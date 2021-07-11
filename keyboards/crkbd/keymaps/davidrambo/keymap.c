/* Copyright 2021 David Rambo
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

//extern uint8_t is_master;


enum custom_layers {
    _COLEMAK,
    _SYMBOL,
    _NAVIGATION,
    _FKEYS,
};

//keycode shorthands
#define SYM  MO(1)
#define NAV  LT(2, KC_ESC)
#define FKEY MO(3)

//aliases for clarity in layering
#define SftEnt SFT_T(KC_ENT)   // Shift when held, Enter when tapped
#define BSCTL  LCTL_T(KC_BSPC) // Ctrl when held, Backspace when tapped
#define CTAB   LCTL(KC_TAB)
#define ATAB   LALT(KC_TAB)

//aliases for Navigation layer
#define CBSPC LCTL(KC_BSPC)  // delete whole word
#define C_CL   LCTL(KC_LEFT) // move cursor one word back
#define C_CR   LCTL(KC_RGHT) // move cursor one word forward

//internet browser tab shortcuts and window swapping
#define CTLPGDN LCTL(KC_PGDN)
#define CTLPGUP LCTL(KC_PGUP)

#define G_GRV   LGUI(KC_GRV)
#define SftEnt  SFT_T(KC_ENT)

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,
  SET_RGB,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                        KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      NAV   ,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                        KC_H,    KC_N,    KC_E,    KC_I, KC_O   , KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  SftEnt,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, KC_LGUI,   BSCTL,   KC_SPC,   SYM ,   FKEY
                                      //`--------------------------'  `--------------------------'

  ),

  [_SYMBOL] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_LBRC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_RBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSLS, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_END,  _______, _______, _______,                       KC_GRV, KC_MINS, KC_PGUP, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, KC_PGDN
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAVIGATION] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      CTAB ,   C_CL  ,   KC_UP,   C_CR  ,  KC_DEL, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                     CTLPGUP, KC_LEFT , KC_DOWN, KC_RGHT, CTLPGDN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        RESET, _______, _______, _______, _______, _______,                      ATAB   , CBSPC , KC_HOME, KC_END,    G_GRV , _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_FKEYS] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, RGB_SAI, RGB_HUI, RGB_VAI, RGB_TOG, SET_RGB,                     _______, _______, _______, _______, _______,  _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, RGB_MOD, RGB_M_P, KC_VOLD, KC_VOLU, KC_MPLY,                     _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,     _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

void keyboard_post_init_user(void) {
//    rgb_matrix_sethsv(191, 43, 81);
    rgblight_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        
        case SET_RGB:
            if (record->event.pressed) {
                rgb_matrix_sethsv_noeeprom(18, 86, 95);
            }
            return false;
            break;

    }
    return true;
}
