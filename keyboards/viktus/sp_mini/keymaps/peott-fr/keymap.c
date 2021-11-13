 /* Copyright 2021 peott
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

// Layers by name
enum custom_layers {
    _BASE,
    _LHAND,
    _RHAND,
    _NUM
};

// Layers defined by function
#define LHAND LT(_LHAND,KC_SPC)
#define RHAND LT(_RHAND,KC_BSPC)
#define NUM TG(_NUM)
// Keycodes for cleaner code
#define L_CTRL LCTL_T(KC_MPRV)
#define L_ALT LALT_T(KC_MNXT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_all(
        KC_MPLY, KC_GRV,  KC_1,    KC_2,  KC_3,  KC_4,  KC_5,    KC_6,  KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS,
        KC_TRNS, KC_TAB,  KC_Q,    KC_W,  KC_E,  KC_R,  KC_T,    KC_Y,  KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, NUM,
        KC_TRNS, KC_LCTL, KC_A,    KC_S,  KC_D,  KC_F,  KC_G,    KC_H,  KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_DEL,
        KC_TRNS, KC_LSPO, KC_Z,    KC_X,  KC_C,  KC_V,  KC_B,    KC_N,  KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,
        KC_TRNS, L_CTRL,  KC_LGUI, L_ALT, KC_NO, LHAND,          RHAND, KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_LHAND] = LAYOUT_all(
        RESET,   KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,
        KC_HOME, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS,     RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_TRNS, KC_TRNS,
        KC_PGUP, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ENT,  KC_TRNS,
        KC_PGDN, KC_LSFT, KC_CALC, KC_MYCM, KC_TRNS, KC_ENT,  KC_BSPC,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSPC, KC_TRNS,
        KC_END,  KC_LCTL, KC_TRNS, KC_LALT, KC_TRNS, KC_TRNS,              KC_TRNS, KC_RALT, KC_RCTL, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_RHAND] = LAYOUT_all(
        KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,  KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO, KC_GRV,  KC_1,    KC_2,  KC_3,    KC_4,   KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, KC_BSLS,
        KC_NO, KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_PLUS, KC_NO,   KC_PIPE,
        KC_NO, KC_LSFT, KC_NO,   KC_NO, KC_NO,   KC_NO,  KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RSPC, KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),
    [_NUM] = LAYOUT_all(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_NO, KC_NO, KC_NO, KC_F13,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_NO, KC_NO, KC_NO, NUM,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_P4,   KC_P5,   KC_P6,   KC_PCMM, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_P1,   KC_P2,   KC_P3,   KC_PEQL, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_P0,   KC_PDOT, KC_PENT, KC_NO,   KC_NO, KC_NO
    )
};

void keyboard_pre_init_user(void) {
    setPinOutput(F5);  // initialize F5 for LED
    setPinOutput(F6);  // initialize F6 for LED
    setPinOutput(F7);  // initialize F7 for LED
}

layer_state_t layer_state_set_user(layer_state_t state) {
    writePinLow(F5);
    writePinLow(F6);
    writePinLow(F7);
    switch (get_highest_layer(state)) {
        case _LHAND:
            writePinHigh(F5);
            break;
        case _RHAND:
            writePinHigh(F6);
            break;
        case _NUM:  // replace 'XXXX' with the layer or function name
            writePinHigh(F7);
            break;
        case KC_F13:
            writePinHigh(F7);
            writePinHigh(F5);
            writePinHigh(F6);
            break;
        }
    return state;
}

bool spongebob_mode = false;
bool spongebob_case = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (spongebob_mode) {
    switch(keycode) {
      case KC_A...KC_Z:
        if (record->event.pressed) {
          (spongebob_case ^= 1) == 0 ? tap_code16(S(keycode)) : tap_code(keycode);
          return false; break;
        }
    }
  }
  switch(keycode) {
    case KC_F13:
      if (record->event.pressed) {
        spongebob_mode ^= 1;
      }
      return false; break;
  }
  return true;
}


