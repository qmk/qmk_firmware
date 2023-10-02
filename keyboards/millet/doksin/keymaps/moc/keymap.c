/* Copyright 2021 Atsushi Nagase
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

enum meishi2_moc_layers {
    _DEFAULT,
    _RAISE
};

#define PRO_MICRO_LED_TX D5
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DEFAULT] = LAYOUT( /* Base */
    RAISE, KC_B, KC_N, KC_SPC
  ),
  [_RAISE] = LAYOUT( /* Raise */
    _______, KC_LEFT, KC_RGHT, LSFT(KC_S)
  )
};

void matrix_init_user(void) {
  setPinOutput(PRO_MICRO_LED_TX);
  writePinHigh(PRO_MICRO_LED_TX);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode == RAISE) {
    writePin(PRO_MICRO_LED_TX, !record->event.pressed);
  }
  return true;
}
