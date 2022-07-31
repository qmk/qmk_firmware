/* Copyright 2021 James Won <me@jwon.me>
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
    _BASE_DVORAK,
    _RAISE_DVORAK,
    _KEYPAD,
    _QWERTY,
};

// Mac-specific macros
#define MACCOPY LGUI(KC_C)
#define MACPAST LGUI(KC_V)
#define MACUNDO LGUI(KC_Z)
#define MACREDO LGUI(KC_Y)
#define MACLOCK LGUI(LCTL(KC_Q))

#define LSA_ LSA(KC_NO)
#define SFT_ESC SFT_T(KC_ESC)
#define KEYPAD TG(_KEYPAD)
#define QWERTY TG(_QWERTY)
#define RAISE MO(_RAISE_DVORAK)

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE_DVORAK] = LAYOUT (
           // Left Hand
           MACLOCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
           KC_PIPE, KC_PLUS, KC_LBRC, KC_LCBR, KC_LPRN, KC_AMPR,
           KC_TAB,  KC_SCLN, KC_COMM, KC_DOT,  KC_P,    KC_Y,
           SFT_ESC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,
           KC_LCTL, KC_QUOT, KC_Q,    KC_J,    KC_K,    KC_X,
                    KC_DLR,  KC_BSLS, KC_LEFT, KC_RGHT,
           // Left Thumb
                    KC_LGUI, KC_LALT,
                             MACPAST,
           KC_BSPC, KC_SPC,  MACCOPY,

           // Right Hand
           KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, QWERTY,  RESET,
           KC_EQL,  KC_RPRN, KC_RCBR, KC_RBRC, KC_ASTR, KC_EXLM,
           KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSLS,
           KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
           KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
                    KC_DOWN, KC_UP,   KC_SLSH, KC_AT,
           // Right Thumb
           KEYPAD,  LSA_,
           MACUNDO,
           MACREDO, RAISE, KC_ENT
    ),

[_RAISE_DVORAK] = LAYOUT (
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
           _______, KC_COLN, KC_LABK, KC_RABK, S(KC_P), S(KC_Y),
           _______, S(KC_A), S(KC_O), S(KC_E), S(KC_U), S(KC_I),
           _______, KC_DQUO, S(KC_Q), S(KC_J), S(KC_K), S(KC_X),
                    KC_TILD, KC_PIPE, _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PERC,
           S(KC_F), S(KC_G), S(KC_C), S(KC_R), S(KC_L), KC_HASH,
           S(KC_D), S(KC_H), S(KC_T), S(KC_N), S(KC_S), KC_UNDS,
           S(KC_B), S(KC_M), S(KC_W), S(KC_V), S(KC_Z), _______,
                    _______, _______, KC_QUES, KC_CIRC,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, _______
    ),

[_KEYPAD] = LAYOUT (
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, KC_NLCK, KC_PEQL, KC_PSLS, KC_PAST, _______,
           _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______,
           _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
           _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
                    _______, _______, KC_PDOT, KC_PENT,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, KC_P0
    ),

[_QWERTY] = LAYOUT(
           // Left Hand
           KC_ESC,  _______, _______, _______, _______, _______, _______, _______, _______,
           KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
           KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
           KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
           KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                    KC_GRV,  KC_INS,  KC_LEFT, KC_RGHT,
           // Left Thumb
                    KC_LGUI, KC_LALT,
                             KC_HOME,
           KC_BSPC, KC_DEL,  KC_END ,

           // Right Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
	       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
	       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
	       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
	       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
		            KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC,
           // Right Thumb
           KC_RGUI, KC_RCTL,
           KC_PGUP,
           KC_PGDN, KC_ENT,  KC_SPC
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _KEYPAD:
        writePinLow(LED_COMPOSE_PIN);
        break;
    case _RAISE_DVORAK:
        writePinLow(LED_NUM_LOCK_PIN);
        break;
    case _QWERTY:
        writePinLow(LED_SCROLL_LOCK_PIN);
        break;
    default: //  for any other layers, or the default layer
        writePinHigh(LED_NUM_LOCK_PIN);
        writePinHigh(LED_SCROLL_LOCK_PIN);
        writePinHigh(LED_COMPOSE_PIN);
        break;
    }
  return state;
}

bool led_update_user(led_t led_state) {
    // Disable led_update_kb() so that layer indication code doesn't get overridden.
    return false;
}

void matrix_scan_user(void) {
    writePin(LED_CAPS_LOCK_PIN, !(get_mods() & MOD_MASK_SHIFT));
}
