/* Copyright 2021 Joshua T.
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

#include "super_alt_tab.h"

// https://docs.qmk.fm/#/feature_macros?id=super-alt%E2%86%AFtab

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

void matrix_scan_super_alt_tab(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > USER_SUPER_ALT_TAB_TIMEOUT) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}


bool process_record_super_alt_tab(uint16_t keycode, const keyrecord_t *record) {
    if (keycode != SALTTAB) {
        return true;
    }

    if (record->event.pressed) {
        if (!is_alt_tab_active) {
            is_alt_tab_active = true;
            register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
    }
    else {
        unregister_code(KC_TAB);
    }

    return false;
}
