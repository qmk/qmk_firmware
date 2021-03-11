/* Copyright 2020 floookay
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

enum adelheid_layers {
  _BASE,
  _SECONDARY
};

// tap dance declarations
enum {
    _TD_CTGU = 0,
    _TD_PGUP = 1,
    _TD_PGDN = 2,
    _TD_HOME = 3,
    _TD_END  = 4,
    _TD_RSHC = 5,
    _TD_PSCR = 6
};

#define MO_SEC MO(_SECONDARY)
#define TD_CTGU TD(_TD_CTGU)
#define TD_PGUP TD(_TD_PGUP)
#define TD_PGDN TD(_TD_PGDN)
#define TD_HOME TD(_TD_HOME)
#define TD_END TD(_TD_END)
#define TD_RSHC TD(_TD_RSHC)
#define TD_PSCR TD(_TD_PSCR)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_F13,  TD_PGUP,

    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,  TD_HOME,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,          TD_END,
    TD_CTGU, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    TD_PGDN,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,
    KC_LCTL,          KC_LALT,          KC_SPC,  MO_SEC,           KC_SPC,           KC_RALT,                   KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_SECONDARY] = LAYOUT(
    KC_SLEP, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,           TD_PSCR, KC_VOLU,

    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_INS,  BL_STEP,
    _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, _______, KC_DEL,           KC_MUTE,
    _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, KC_MPLY,                   KC_VOLD,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TD_RSHC,          KC_MPLY,
    _______,          _______,          _______, _______,          _______,          _______,                   KC_MPRV, KC_MSTP, KC_MNXT
  )
};


// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for first parameter, twice for second
    [_TD_CTGU] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LGUI),
    [_TD_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, LCTL(KC_PGUP)),
    [_TD_PGDN] = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, LCTL(KC_PGDN)),
    [_TD_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, LCTL(KC_HOME)),
    [_TD_END]  = ACTION_TAP_DANCE_DOUBLE(KC_END,  LCTL(KC_END)),
    [_TD_RSHC] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
    [_TD_PSCR] = ACTION_TAP_DANCE_DOUBLE(KC_PSCR, LSFT(LGUI(KC_S))) // screenshot tool tap dance
};
