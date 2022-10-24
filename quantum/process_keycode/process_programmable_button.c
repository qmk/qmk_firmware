/*
Copyright 2021 Thomas Weißschuh <thomas@t-8ch.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "process_programmable_button.h"
#include "programmable_button.h"

bool process_programmable_button(uint16_t keycode, keyrecord_t *record) {
    if (keycode >= QK_PROGRAMMABLE_BUTTON_MIN && keycode <= QK_PROGRAMMABLE_BUTTON_MAX) {
        uint8_t button = keycode - QK_PROGRAMMABLE_BUTTON_MIN + 1;
        if (record->event.pressed) {
            programmable_button_register(button);
        } else {
            programmable_button_unregister(button);
        }
    }
    return true;
}
