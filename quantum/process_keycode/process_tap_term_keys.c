/* Copyright 2020 Vladislav Kucheriavykh
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

#include <stdio.h>
#include "process_tap_term_keys.h"

void tapping_term_report(void) {
    char display[8];

    snprintf(display, 8, "%d", tapping_term);

    send_string((const char *)display);
}

bool process_tap_term_keys(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case TK_PRNT:
                tapping_term_report();
                return true;

            case TK_UP:
                tapping_term += TAP_TERM_INCREMENT;
                return true;

            case TK_DOWN:
                tapping_term -= TAP_TERM_INCREMENT;
                return true;
        }
    }
    return true;
}
