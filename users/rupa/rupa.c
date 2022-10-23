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

#if defined(UNICODE_SCRIPT_MODE_ENABLE)
const font_t * translator = NULL;

// https://en.wikipedia.org/wiki/Mathematical_Alphanumeric_Symbols
static const font_t *fonts_map[] = {
    [F_FRACT] = &(font_t){0x1D56C, 0x1D586, 0x1D7D8}, // fraktur/doublestruck numbers
    [F_ITALI] = &(font_t){0x1D468, 0x1D482, 0x1D7CE}, // italic/bold numbers
    [F_MONOS] = &(font_t){0x1D670, 0x1D68A, 0x1D7F6}, // monospace
    [F_NORML] = &(font_t){0x1D400, 0x1D41A, 0x00030}, // normal!
    [F_SANSI] = &(font_t){0x1D63C, 0x1D656, 0x1D7EC}, // sans 1talic/sans bold numbers
    [F_SANSN] = &(font_t){0x1D5D4, 0x1D5EE, 0x1D7E2}, // sans normal/sans numbers
    [F_SCRPT] = &(font_t){0x1D4D0, 0x1D4EA, 0x1D7CE}, // script/bold numbers
};

/*
font_t doublestruc = {0x1D538, 0x1D552, 0x1D7D8};
uint_32 []snowflakes = {
  // doublestruck
  0x1D53B, // C
  0x1D540, // H
  0x1D546, // N
  0x1D548, // P
  0x1D549, // Q
  0x1D54A, // R
  0x1D552, // Z
};
*/

const font_t *get_script_mode(void) {
    return translator;
}
bool set_script_mode(int fc) {
    translator = translator == fonts_map[fc] ? NULL : fonts_map[fc];
    dprintf("set_script_mode: %u %b\n", fc, translator != NULL);
    return true;
}

// Maps A-Z, a-z, and 0-9 to other unicode ranges. We also map space to EN
// SPACE for some reason :)
uint32_t map_alnum(const font_t *f, bool is_shifted, uint32_t keycode) {
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

bool script_mode_translate(bool is_shifted, uint32_t keycode) {
    uint32_t translated = map_alnum(translator, is_shifted, keycode);
    if (translated == 0) return true;
    dprintf("script_mode_translate: %u => %d\n", keycode, translated);
    register_unicode(translated);
    return false;
}
#endif
