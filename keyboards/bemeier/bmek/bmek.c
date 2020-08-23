/* Copyright 2020 bemeier
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
#include "bmek.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BM_RST:  // RESET KEYBOARD
            if (record->event.pressed) break;
            for (int i = 0; i < RGBLED_NUM; i++) {
                rgblight_sethsv_at(255, 255, 255, i);
            }
            reset_keyboard();
            break;
    }

    return process_record_user(keycode, record);
}
