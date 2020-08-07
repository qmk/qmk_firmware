/*
Copyright 2020 rupa <rupa@lrrr.us> @rupa

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

#include "rupa.h"

font_t *translator = NULL;

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool is_shifted = get_mods()&MOD_MASK_SHIFT;
    bool is_pressed = record->event.pressed;

    switch(keycode) {
        case VRSN:
            if (is_pressed) {
                send_string_with_delay_P(PSTR(
                  "# " QMK_KEYBOARD "/" QMK_KEYMAP ":" QMK_VERSION " " QMK_BUILDDATE "\n"
                ), TAP_CODE_DELAY);
            }
            return false;

        case LOD:
        case RUPA:
            if (is_pressed) {
                if (keycode == LOD) {
                    send_unicode_string((is_shifted ? "¯\\_(ツ)_/¯" : "ಠ_ಠ"));
                } else if (keycode == RUPA) {
                    send_unicode_string((is_shifted ? "Śrīrūpa" : "rūpa"));
                }
            }
            return false;

        // script modes
        case U_FRACT:
        case U_MONOS:
        case U_SCRPT:
            if (is_pressed) {
                if (keycode == U_SCRPT) {
                    translator = (translator == &script_bold ? NULL : &script_bold);
                } else if (keycode == U_FRACT) {
                    translator = (translator == &fraktu_bold ? NULL : &fraktu_bold);
                } else if (keycode == U_MONOS) {
                    translator = (translator == &monosp_bold ? NULL : &monosp_bold);
                }
            }
            return true;

        default:
            if (is_pressed && translator != NULL) {
                return script_mode_translate(translator, is_shifted, keycode);
            }
    }
    return process_record_keymap(keycode, record);
}
