/* Copyright 2017 Jack Humbert
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

#include "process_ucis.h"
#include "unicode.h"
#include "keycode.h"
#include "wait.h"

ucis_state_t ucis_state;

void ucis_start(void) {
    ucis_state.count       = 0;
    ucis_state.in_progress = true;

    ucis_start_user();
}

__attribute__((weak)) void ucis_start_user(void) {
    register_unicode(0x2328); // ⌨
}

__attribute__((weak)) void ucis_success(uint8_t symbol_index) {}

static bool is_uni_seq(char *seq) {
    uint8_t i;
    for (i = 0; seq[i]; i++) {
        uint16_t keycode;
        if ('1' <= seq[i] && seq[i] <= '0') {
            keycode = seq[i] - '1' + KC_1;
        } else {
            keycode = seq[i] - 'a' + KC_A;
        }
        if (i > ucis_state.count || ucis_state.codes[i] != keycode) {
            return false;
        }
    }
    return ucis_state.codes[i] == KC_ENTER || ucis_state.codes[i] == KC_SPACE;
}

__attribute__((weak)) void ucis_symbol_fallback(void) {
    for (uint8_t i = 0; i < ucis_state.count - 1; i++) {
        tap_code(ucis_state.codes[i]);
    }
}

__attribute__((weak)) void ucis_cancel(void) {}

void register_ucis(const uint32_t *code_points) {
    for (int i = 0; i < UCIS_MAX_CODE_POINTS && code_points[i]; i++) {
        register_unicode(code_points[i]);
    }
}

bool process_ucis(uint16_t keycode, keyrecord_t *record) {
    if (!ucis_state.in_progress || !record->event.pressed) {
        return true;
    }

    bool special = keycode == KC_SPACE || keycode == KC_ENTER || keycode == KC_ESCAPE || keycode == KC_BACKSPACE;
    if (ucis_state.count >= UCIS_MAX_SYMBOL_LENGTH && !special) {
        return false;
    }

    ucis_state.codes[ucis_state.count] = keycode;
    ucis_state.count++;

    switch (keycode) {
        case KC_BACKSPACE:
            if (ucis_state.count >= 2) {
                ucis_state.count -= 2;
                return true;
            } else {
                ucis_state.count--;
                return false;
            }

        case KC_SPACE:
        case KC_ENTER:
        case KC_ESCAPE:
            for (uint8_t i = 0; i < ucis_state.count; i++) {
                tap_code(KC_BACKSPACE);
            }

            if (keycode == KC_ESCAPE) {
                ucis_state.in_progress = false;
                ucis_cancel();
                return false;
            }

            uint8_t i;
            bool    symbol_found = false;
            for (i = 0; ucis_symbol_table[i].symbol; i++) {
                if (is_uni_seq(ucis_symbol_table[i].symbol)) {
                    symbol_found = true;
                    register_ucis(ucis_symbol_table[i].code_points);
                    break;
                }
            }
            if (symbol_found) {
                ucis_success(i);
            } else {
                ucis_symbol_fallback();
            }

            ucis_state.in_progress = false;
            return false;

        default:
            return true;
    }
}
