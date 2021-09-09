/* Copyright 2021 Rocco Jiang
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

#include "do43.h"

/* OLED display modes */
oled_mode_t oled_mode = OLED_INFO;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // Perform _kb actions only if process_record_user() didn't already handle the key event
    // https://github.com/qmk/qmk_firmware/issues/8246
    if (!process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
      case OLED_TOGG:
        if (record->event.pressed) {
            // When keycode OLED_TOGG is pressed
            oled_clear();
            oled_mode = (oled_mode + 1) % _NUM_OLED_MODES;
        }
    }

    return true;
}
