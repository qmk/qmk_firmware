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

#include <print.h>
#include "rupa.h"

// https://en.wikipedia.org/wiki/Mathematical_Alphanumeric_Symbols
font_t script_bold = {0x1D4D0, 0x1D4EA, 0x1D7CE}; // with bold numbers
font_t fraktu_bold = {0x1D56C, 0x1D586, 0x1D7D8}; // with doublestruck numbers
font_t monosp_bold = {0x1D670, 0x1D68A, 0x1D7F6};

// Maps A-Z, a-z, and 0-9 to other unicode ranges. We also map space to EN
// SPACE for some reason :)
uint32_t map_alnum(font_t *f, bool is_shifted, uint32_t keycode) {
    switch (keycode) {
        case KC_SPACE:
            return (is_shifted ? 0 : 0x2002); // EN SPACE
        case KC_0:
            return (is_shifted ? 0 : f->zero_glyph);
        case KC_A ... KC_Z:
            return (is_shifted ? f->upper_alpha : f->lower_alpha) + keycode - KC_A;
        case KC_1 ... KC_9:
            return (is_shifted ? 0 : f->zero_glyph + keycode - KC_1 + 1);
        default:
            return 0;
    }
}

bool script_mode_translate(font_t *translator, bool is_shifted, uint32_t keycode) {
    uint32_t translated = map_alnum(translator, is_shifted, keycode);
    if (translated == 0) return true;
    dprintf("script_mode_translate: %u => %d\n", keycode, translated);
    register_unicode(translated);
    return false;
}
