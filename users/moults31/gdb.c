/* Copyright 2021 moults31
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
#include "gdb.h"

bool process_record_gdb(uint16_t keycode, keyrecord_t *record) {
    bool rv = true;
    switch (keycode) {
        case M_GDB_PLAY:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_F5));
            }
            break;
        case M_GDB_PAUSE:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_F6));
            }
            break;
        case M_GDB_STEPOVER:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_F10));
            }
            break;
        case M_GDB_STEPIN:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_F11));
            }
            break;
        case M_GDB_STEPOUT:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_F11)));
            }
            break;
        case M_GDB_RESTART:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_F5))));
            }
            break;
        case M_GDB_STOP:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_F5)));
            }
            break;
    }

    return rv;
}
