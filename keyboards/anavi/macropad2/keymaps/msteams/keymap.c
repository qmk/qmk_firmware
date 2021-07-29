/* Copyright 2021 Leon Anavi <leon@anavi.org>
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

/*
 * This keymap contains the following shortcuts for Microsoft Teams
 * on MS Windows and GNU/Linux distributions:
 *
 * Ctrl+Shift+M: Toggle mute
 * Ctrl+Shift+O: Toggle video (doesn't work in a web browser)
 *
 * NOTE: Mac users should replace Ctrl with Command in all
 * shortcuts
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    LCTL(LSFT(KC_M)),  LCTL(LSFT(KC_O))
  )
};

const uint16_t PROGMEM test_combo[] = {LCTL(LSFT(KC_M)), LCTL(LSFT(KC_O)), COMBO_END};
combo_t key_combos[COMBO_COUNT] = {COMBO_ACTION(test_combo)};

void process_combo_event(uint16_t combo_index, bool pressed) {
	backlight_step();
}
