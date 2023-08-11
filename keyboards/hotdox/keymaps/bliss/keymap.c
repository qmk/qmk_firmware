/* Copyright 2021 Benjamin Chausse
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
#include "version.h"

enum layer_names {
    BASE, // default layer
    FUNC, // functions keys, numbpad, and arrows
};

enum custom_keycodes {
  VRSN = SAFE_RANGE,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: default layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |    `   |   1  |   2  |   3  |   4  |   5  |   6  |           |   7  |   8  |   9  |   0  |   -  |   =  |  BkSp  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |   {  |           |  }   |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | TUX    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | '/TUX  |
 * |--------+------+------+------+------+------|   ^  |           |  &   |------+------+------+------+------+--------|
 * | Shft/( |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | Shft/) |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ctrl |  Alt | Caps |  MP1 | FUNC |                                       |  MR1 |  MS1 |   [  |   ]  | TFUNC |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |      | Prnt |       | INS  |  HOME  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Vol+ |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Enter |  :   |
 *                                 |      |ace   | Vol- |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 *
 * MR1: Record macro 1               Prnt: Print Screen
 * MS1: Stop recording macro 1       INS: INSERT
 * MP1: Play macro 1                 TFUNC: Goto FUNC only while pressed
 * FUNC: Set FUNC as default layer
 *
 *
 */

/* If it accepts an argument (i.e, is a function), it doesn't need KC_. */
/* Otherwise, it needs KC_* */
	[BASE] = LAYOUT_ergodox( /* layer 0: default */
      /* Left hand */
      KC_GRV,               KC_1,    KC_2,    KC_3,    KC_4,  KC_5, KC_6,
      KC_TAB,               KC_Q,    KC_W,    KC_E,    KC_R,  KC_T, LSFT(KC_LBRC),
      MT(MOD_LGUI, KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,  KC_G,
      SC_LSPO,              KC_Z,    KC_X,    KC_C,    KC_V,  KC_B, LSFT(KC_6),
      KC_LCTL,              KC_LALT, KC_CAPS, DM_PLY1, DF(1),

      KC_NO, KC_PSCR,
      KC_VOLU,
      KC_SPC, KC_BSPC, KC_VOLD,

      /* right hand */
      KC_7,          KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,                KC_BSPC,
      RSFT(KC_RBRC), KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,                  KC_BSLS,
      KC_H,          KC_J,    KC_K,    KC_L,    KC_SCLN, MT(MOD_RGUI, KC_QUOT),
      RSFT(KC_7),    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,               SC_RSPC,
      DM_REC1,       DM_RSTP, KC_LBRC, KC_RBRC, MO(1),

      KC_INS,  KC_HOME,
      KC_PGUP,
      KC_PGDN, KC_ENT,  RSFT(KC_SCLN)),

/* Keymap 1: function keys, numpad, and arrows
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  | F10  | F11  | F12  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |  UP  |      |      |      |           |      |   /  |   7  |   8  |   9  |   -  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | LEFT | DOWN |RIGHT |      |------|           |------|   *  |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |   %  |   1  |   2  |   3  |   ,  | Shft/) |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ctrl |  Alt | Caps |      | MAIN |                                       |   0  |   .  |  [   |   ]  |       |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |      | Prnt |       | Ins  |  Home  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Vol+ |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Enter | Equal|
 *                                 |      |ace   | Vol- |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */

	[FUNC] = LAYOUT_ergodox( /* layer 1: func */
    /* left hand */
    KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F6,
    KC_NO,   KC_NO,   KC_NO,   KC_UP,   KC_NO,   KC_NO, KC_NO,
    KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
    KC_LCTL, KC_LALT, KC_CAPS, KC_NO,   DF(0),

    KC_NO,   KC_PSCR,
    KC_VOLU,
    KC_SPC,  KC_BSPC, KC_VOLD,

    /* right hand */
    KC_F7,   KC_F8,      KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,
    KC_NO,   KC_PSLS,    KC_P7,   KC_P8,   KC_P9,   KC_PMNS, KC_BSLS,
    KC_PAST, KC_P4,      KC_P5,   KC_P6,   KC_PPLS, KC_NO,
    KC_NO,   LSFT(KC_5), KC_P1,   KC_P2,   KC_P3,   KC_PCMM, SC_RSPC,
    KC_P0,   KC_PDOT,    KC_LBRC, KC_RBRC, KC_NO,

    KC_INS,  KC_HOME,
    KC_PGUP,
    KC_PGDN, KC_ENT,  KC_PEQL)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = get_highest_layer(layer_state);

    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }
};
