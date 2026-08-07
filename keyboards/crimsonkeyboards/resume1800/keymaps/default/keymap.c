/* Copyright 2022 CrimsonKeyboards
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

enum custom_keycodes {
    KC_00 = SAFE_RANGE, //Double Zero
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_00:
        if (record->event.pressed) {
            // when keycode KC_00 is pressed
            SEND_STRING("00");
        } else {
            // when keycode KC_00 is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ansi_all(
  /*    Esc      F1       F2       F3       F4      F5      F6      F7      F8      F9       F10      F11       F12      F13      F14     Print     Scroll Lock   Pause   Insert    End		*/
	  KC_ESC, 	KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_F13,  KC_F14, KC_PSCR,   KC_SCRL,     KC_PAUS, KC_INS,  KC_END,
  /*    ~         1        2        3        4       5       6       7       8       9        0        -         =     Backspace          Delete    Num Lock      Num /   Num *     Num -	*/
      KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,         KC_DELETE, KC_NUM_LOCK, KC_PSLS, KC_PAST, KC_PMNS, 
  /*    Tab       Q        W        E        R       T       Y       U       I       O        P        [          ]       \               Home      Num 7        Num 8    Num 9     N/A		*/
      KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,         KC_HOME,   KC_P7,       KC_P8,   KC_P9,   KC_TRNS,	
  /*    Caps      A        S        D        F       G       H       J       K       L        ;        '        Enter                    Page Up    Num 4        Num 5    Num 6     Num +	*/
      KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_ENT,                   KC_PGUP,   KC_P4,       KC_P5,   KC_P6,   KC_PPLS,
  /* Left Shift            Z        X        C       V       B       N       M       ,        .        /       R Shift   Up             Page Down   Num 1        Num 2    Num 3     N/A		*/
      KC_LSFT,           KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,           KC_PGDN,   KC_P1,       KC_P2,   KC_P3,   KC_TRNS,	
  /* L Control  Windows  L Alt                             Space                    R Alt     Fn    R Control   Left     Down             Right     Num 00       Num 0    Num .   Num Enter	*/
      KC_LCTL,  KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, MO(1),   KC_RCTL,  KC_LEFT, KC_DOWN,         KC_RIGHT,  KC_00,       KC_P0,   KC_PDOT, KC_PENT)
};
