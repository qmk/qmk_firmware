/* Copyright 2016 Jack Humbert
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

#include "process_unicode.h"
#include "unicode.h"
#include "keycodes.h"
#include "quantum_keycodes.h"

bool process_unicode(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (keycode >= QK_UNICODE && keycode <= QK_UNICODE_MAX) {
            register_unicode(QK_UNICODE_GET_CODE_POINT(keycode));
        }
    }
    return true;
}
