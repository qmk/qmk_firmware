 /* Copyright 2020 RGBKB
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
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#include QMK_KEYBOARD_H

enum layer_number {
    _QWERTY,
    _COLEMAK,
    _FN,
    _ADJ
};

#define FN_ESC   LT(_FN, KC_ESC)
#define FN_CAPS  LT(_FN, KC_CAPS)
#define QWERTY   DF(_QWERTY)
#define COLEMAK  DF(_COLEMAK)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_all(
        QK_GESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, KC_DEL,
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        FN_CAPS,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT,   KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC,
        KC_LCTL,   KC_LGUI, KC_LALT, RM_TOGG, MO(_ADJ),KC_SPC, KC_SPC, MO(_FN), KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
    ),

    [_COLEMAK] = LAYOUT_all(
        QK_GESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, KC_DEL,
        KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,   KC_J,   KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
        FN_CAPS,   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,   KC_H,   KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
        KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC, KC_ENT,
        KC_LCTL,   KC_LGUI, KC_LALT, RM_TOGG, MO(_ADJ),KC_SPC, KC_SPC, MO(_FN), KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
    ),

    [_FN] = LAYOUT_all(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_PSCR,
        _______, KC_PGDN, KC_UP,   KC_PGUP, _______, _______, _______, KC_PGDN, KC_UP,   KC_PGUP, KC_PSCR, KC_HOME,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,  KC_END,
        _______, _______, _______, _______, _______, _______, _______, KC_LBRC, _______, KC_RBRC, _______, _______, _______,
        _______, _______, _______, RM_NEXT, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_ADJ] = LAYOUT_all(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_PSCR,
        _______, RM_SATD, RM_VALU, RM_SATU, QK_BOOT, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______,
        _______, RM_HUED, RM_VALD, RM_HUEU, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______, _______,
        _______, RM_SPDD, _______, RM_SPDU, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, _______, _______,
        _______, _______, _______, RM_NEXT, _______, _______, _______, KC_P0,   KC_PDOT, KC_NUM,  _QWERTY, _COLEMAK
    )
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("RGBKB Pan\n"), false);
    oled_write_P(PSTR("Layer: "), false);
    uint8_t layer = get_highest_layer(layer_state|default_layer_state);
    switch (layer) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _COLEMAK:
            oled_write_P(PSTR("Colemak\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("Function\n"), false);
            break;
        case _ADJ:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            //oled_write_ln_P(PSTR("Undefined"), false);
    }
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("Numlock On\n") : PSTR("           \n"), false);
    oled_write_P(led_state.caps_lock ? PSTR("Capslock On \n") : PSTR("           \n"), false);

    return false;
}
#endif

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {         // First encoder - right
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  } else if (index == 1) {  // Second encoder - left
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  }
    return true;
}
