/*
 * Copyright 2021 QMK
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_fullmatrix_8x18(
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R,
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R,
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R,
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R,
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R,
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R,
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R,
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R
  )
};

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;
    // debug_mouse=true;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
    return true;
}
