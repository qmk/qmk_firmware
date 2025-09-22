/* Copyright 2025 Soldered Electronics <hello@soldered.com>
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

// Layer 0: media + utilities
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MPRV,     // Previous Track  (was Play/Pause)
        KC_MNXT,     // Next Track
        KC_MPLY,     // Play / Pause    (swapped with Previous)
        KC_CALC,     // Launch Calculator
        KC_MAIL,     // Launch Email client
        KC_NO        // Placeholder - encoder button handled separately
    )
};

// Handle encoder rotation
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU); // Volume Up
        } else {
            tap_code(KC_VOLD); // Volume Down
        }
        return false;
    }
    return true;
}

// Handle encoder press (mute system audio)
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Encoder button is wired into matrix position [0,5] (last key in layout)
    if (keycode == KC_NO && record->event.pressed) {
        tap_code(KC_MUTE);
        return false; // stop further processing
    }
    return true;
}
