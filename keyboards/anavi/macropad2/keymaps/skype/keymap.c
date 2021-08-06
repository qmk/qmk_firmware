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
 * The keymap contains the following shortcuts for Skype on
 * MS Windows and GNU/Linux distributions:
 *
 * Ctrl+M: Mute/unmute microphone
 * Ctrl+Shift+K: Start/stop camera
 *
 * NOTE: Mac users should change the shortcut to toggle the mic
 * to Command+Shift+M, for example KC_LGUI(LSFT(KC_M))
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    LCTL(KC_M),  LCTL(LSFT(KC_K))
  )
};

const uint16_t PROGMEM test_combo[] = {LCTL(KC_M), LCTL(LSFT(KC_K)), COMBO_END};
combo_t key_combos[COMBO_COUNT] = {COMBO_ACTION(test_combo)};

void process_combo_event(uint16_t combo_index, bool pressed) {
	backlight_step();
}
